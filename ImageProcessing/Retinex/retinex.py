import cv2 as cv
import numpy  as np
import os

def cov2D (image,kernal,stride=1):
    '''
    # 卷积函数 same padding ,stride 默认为 1,不加 bias
    :param image:
    :param kernal: 滤波器，其size为奇数 nd 数组
    :return:
    '''
    image = np.array(image,dtype=np.float32)
    new_image = image.copy()
    image_shape = image.shape
    k_shape = kernal.shape
    padding =[
        ((stride-1)*image_shape[i]+ k_shape[i] - stride)/2 for i in range(2)
    ]
    if padding[0] %2 != 0:
        padding_i =(int(padding[0]), int(padding[0] + 1))
    else:
        padding_i = (int(padding[0]), int(padding[0] ))
    if padding[1]%2 !=0:
        padding_j = (int(padding[1]), int(padding[1] + 1))
    else:
        padding_j = (int(padding[1]), int(padding[1] ))
    image = np.pad(image,(padding_i,padding_j),'constant')
    # 卷积操作
    for i in range(new_image.shape[0]):
        for j in range(new_image.shape[1]):
            new_image[i][j] = np.sum(image[i*stride:i*stride+k_shape[0],j*stride:j*stride+k_shape[1]] * kernal)
    return new_image

def linear_stretch(input):
    #对灰度进行线性拉伸
    if len(input.shape) <3:
        shape = [input.shape[0],input.shape[1],1]
        input = np.resize(input,shape)
    for i in range(input.shape[-1]):
        max_value = np.max(input[:,:,i])
        min_value = np.min(input[:,:,i])
        scale = 255/(max_value-min_value)
        input[:,:,i] = (input[:,:,i]-min_value)*scale
    return input

def cal_gauss_kernal(gauss_c, kernal_size=[3,3]):
    '''
    计算高斯核函数
    :param gauss_c: 高斯环绕尺度
    :param kernal_size: 核大小, 为方便起见长和宽必须为奇数，如果输入为偶数的话会将其+1变为奇数  [h,w]
    :return: 高斯核 一个 rank=2的 numpy数组
    '''
    h,w = kernal_size
    gauss_c_2 = np.square(gauss_c)
    if h%2 == 0:
        h=h+1
    if w%2 ==0:
        w=w+1
    center = [h//2,w//2]
    kernal = np.zeros(kernal_size,dtype= np.float32)
    for i in range(kernal_size[0]):
        for j in range(kernal_size[1]):
            #遍历计算kernal
            y = np.abs(i-center[0])
            x = np.abs(j-center[1])
            kernal[i][j] = np.exp(-(np.square(x)+ np.square(y))/gauss_c_2 )   # e ^ ( -(x^2 + y^2)/c^2)
    lam = np.sum(kernal)
    return kernal/lam

#利用 retinex算法实现图像对比度增强
def retinex_ssr(input,gauss_c=80,kernal_size=[3,3]):
    '''
    采用 单尺度比较简单的retinex ssr算法 ， 算法思想：  r(x,y) = s(x,y) - l(x,y) (r,s,l 是对数化后的值）
    l(x,y)是光照函数，我们认为光照函数变化比较平滑，在ssr中 采用 高斯滤波器进行近似，即：
    r(x,y) = s(x,y) - log( F(x,y) ** S(x,y))    (**表示卷积）
    F(x,y) = lambda * e ^ ( -(x^2 + y^2)/c^2) （c是高斯环绕尺度，lambda是一个自适应尺度，再确定c的情况下 使得F积分为1）
    :param input: 输入，可以是灰度图像也可以是彩色图像，尝试写自适应算法
    :param gauss_c: 高斯标准差 c
    :return: 处理之后的图像
    '''
    input = np.array(input,dtype=np.float32)
    shape = input.shape
    # if len(shape)==2:
    #     #如果是灰度图
    #     input = np.expand_dims(input,-1) #增加一维
    kernal = cal_gauss_kernal(gauss_c,kernal_size)
    input_L = np.copy(input)
    # for i in range( input_L.shape[-1]):
    #     #     #遍历通道
        #     #     print('###################################################')
    #     #     #input_L[:,:,i] = cov2D( input_L[:,:,i],kernal,1)
    #     #     input_L[:,:,i] = input_L[:,:,i] * kernal
    # h, w = kernal_size
    # if h%2 == 0:
    #     h=h+1
    # if w%2 ==0:
    #     w=w+1
    # input_L = cv.GaussianBlur(input,(h,w),gauss_c)
    # input_L = np.multiply(input_L,kernal)
    # input_L = np.average(input_L)
    input_L = cv.filter2D(input_L,-1,kernal)
    input = np.clip(input,0.000001,255)
    input_L = np.clip( input_L , 0.000001, 255)
    input = np.log(input)
    input_L= np.log(input_L)
    output = input - input_L
    #output = np.exp(output)
    #output = linear_stretch(output)
    #output = np.array(output,dtype= np.uint8)
    output  = input + 6*output
    output = np.exp(output)
    return np.resize(output,shape)


if __name__ =='__main__':
    BASE_PATH = os.path.dirname(os.path.abspath(__file__))
    RESULT_PATH = os.path.join(BASE_PATH, "result")
    if not os.path.exists(RESULT_PATH):
        os.mkdir(RESULT_PATH)
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--img', help="the path of the input img")
    parser.add_argument('--c', help='the param of gauss_c')
    #parser.add_argument('--kernal_size', help='the size of the kernal')
    args = parser.parse_args()
    ################# 图片读取模块
    img_name = os.path.split(args.img)[-1]
    img_name, ext = os.path.splitext(img_name)
    input = cv.imread(args.img, flags=cv.IMREAD_GRAYSCALE) #读取灰度图片
    #input = cv.imread(args.img, flags=cv.IMREAD_COLOR) #读取rgb图片
    ########################## 处理模块
    output = retinex_ssr(input,float(args.c),[input.shape[0],input.shape[1]])
    #########图片输出模块
    img_name = img_name + "_retinex_gauss_" + str(args.c)
    img_name = img_name + ext
    img_name = os.path.join(RESULT_PATH, img_name)
    cv.imwrite(img_name,output)