import numpy as np
import cv2 as cv


def add_gaussian_noise (image,weight,mean=0,sdv=1):
    '''
    给原图像添加一个 正太分布的噪声
    :param image: 原图像 灰度图
    :param weight: 原图像和噪声做加权和的权值
    :param mean: 高斯分布均值 默认为 0
    :param sdv: 高斯分布的方差，默认为1
    :return:
    '''
    image = np.array(image,dtype=np.int32)
    noise = np.random.normal(mean,sdv,image.shape)
    #将图像归一化 为 [-1,1]
    image  = np.array((image-128)/128,dtype=np.float32)
    #添加噪声
    image = image + weight* noise
    #反映射
    image = np.array(image*128+128,dtype=np.int32);
    image = np.clip(image,0,255)
    return image

def add_salt_noise(image,prob):
    '''
    #添加校验噪声，噪声比例为 prob， 高于prob时设置像素值为 255
    :param image:
    :param prob:
    :return:
    '''
    image = np.array(image,dtype=np.int32)
    shape = image.shape
    for i in range(shape[0]):
        for j in range(shape[1]):
            th = np.random.uniform(0,1)
            if th<prob:
                image[i][j]=255
    return image

def add_mean_noise (image,weight,b=-(12**0.5)/2,a=(12**0.5)/2):
    '''
    给原图像添加一个 均值分布的噪声
    :param image: 原图像 灰度图
    :param weight: 原图像和噪声做加权和的权值
    :return:
    '''
    image = np.array(image,dtype=np.int32)
    noise = np.random.uniform(b,a)   # 均值为 0 方差为 1 的均值噪声
    #将图像归一化 为 [-1,1]
    image  = np.array((image-128)/128,dtype=np.float32)
    #添加噪声
    image = image + weight* noise
    #反映射
    image = np.array(image*128+128,dtype=np.int32);
    image = np.clip(image,0,255)
    return image

def cov2D (image,kernal,stride=1):
    '''
    # 卷积函数 same padding ,stride 默认为 1,不加 bias
    :param image:
    :param kernal: 滤波器，其size为奇数 nd 数组
    :return:
    '''
    image = np.array(image,dtype=np.int32)
    new_image = image.copy()
    image_shape = image.shape
    k_shape = kernal.shape
    padding =[
        int (((stride-1)*image_shape[i]+ k_shape[i] - stride)/2) for i in range(2)
    ]
    image = np.pad(image,((padding[0],padding[0]),(padding[1],padding[1])),'constant')
    # 卷积操作
    for i in range(image.shape[0]-k_shape[0]+1):
        for j in range(image.shape[1]-k_shape[1]+1):
            new_image[i,j]  =  np.sum(image[i:i+k_shape[0],j:j+k_shape[1]] * kernal) #

    return new_image

if __name__ =="__main__":
    noise_function={"gaussian":add_gaussian_noise ,"mean":add_mean_noise ,"salt":add_salt_noise}
    kernal1 = np.ones([3,3])/9
    kernal2 = np.array([[1/16,1/8,1/16],[1/8,1/4,1/8],[1/16,1/8,1/16]],dtype=np.float32)
    kernal3 = np.array([[1/25,3/25,1/25],[3/25,9/25,3/35],[1/25,3/25,1/25]],dtype=np.float32)
    kernals =[kernal1,kernal2,kernal3]
    for kernal in kernals:
        print(kernal)
    import os
    BASE_DIR = os.path.dirname(os.path.abspath(__file__))
    IMAGE_PATH = os.path.join(BASE_DIR,"src")
    RESULT_PATH = os.path.join(BASE_DIR,"result");

    images = os.listdir(IMAGE_PATH)
    for image in images:
        ext = os.path.splitext(image)[1]
        imgname = os.path.splitext(image)[0]
        result_sub_path = os.path.join(RESULT_PATH,imgname)
        if not os.path.exists(result_sub_path):
            os.mkdir(result_sub_path)
        for noise_key in noise_function.keys():
            result_sub_sub_path = os.path.join(result_sub_path,noise_key)
            if not os.path.exists(result_sub_sub_path):
                os.mkdir(result_sub_sub_path)
            # 读取图片 灰度图
            image = cv.imread(os.path.join(IMAGE_PATH, imgname+ext),flags=cv.IMREAD_GRAYSCALE)
            #b 保存原图方便对比
            cv.imwrite( os.path.join(result_sub_sub_path,imgname+'_original')+ext,image)
            # 加噪声 对于均值噪声和高斯噪声来说 默认产生 均值为 0 方差为1 的噪声
            if noise_key == "salt":
                noise_image = noise_function[noise_key](image, 0.02)
            else:
                noise_image = noise_function[noise_key](image, 0.1)
            #保存噪声图片
            noise_image_name = os.path.join(result_sub_sub_path,noise_key+"_"+imgname+ext)
            cv.imwrite( noise_image_name,noise_image )
            for i,kernal in enumerate(kernals):
                #滤波
                result_image = cov2D(noise_image,kernal)
                # 保存
                result_name = os.path.join(result_sub_sub_path,noise_key+"_kernal"+str(i)+"_"+imgname+ext)
                cv.imwrite(result_name, result_image)