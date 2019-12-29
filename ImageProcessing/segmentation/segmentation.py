import os
import numpy as np
import cv2 as cv

def otsu(input):
    '''

    :param input: 输入图片是一个numpy数组，深度为1
    :return: output: 分割之后的结果
    '''
    hist,edges =  np.histogram(input,256,[0,256],density=True ) #hist是概率密度分布,计算概率分布，这一步自己实现也很简单只需要遍历input统计即可
    cdf = hist.cumsum()                                        # cdf将概率密度求和, cdf[k] 就是 i 从 0 到 k (包括k ) pi的求和
    mean_global =  np.sum(np.arange(256)*hist )                        #计算全局均值
    var_k_array = np.zeros(256)
    for k in range(256):
        mean_k = np.sum(np.arange(k+1)*hist[0:k+1] ) #计算 m_k  ;m_k 为  i 从 0 到 k (包括k) i*pi的求和
        if cdf[k] ==1 or cdf[k] ==0:
            continue
        temp_var = np.power((mean_global*cdf[k]-mean_k),2)/(cdf[k]*(1-cdf[k]))
        var_k_array[k] = temp_var
    max_var_betweet_class = np.max(var_k_array)      # 求出最大的类间方差
    threshold  = np.average(np.where(var_k_array==max_var_betweet_class))   # 将所有等于类间最大方差的k值 求平均 计算出分割阈值
    mask = (input > threshold)              #输入的图片 所有灰度值 > 阈值的设置为 true
    output = np.zeros(input.shape, dtype = np.uint8)      #初始化0矩阵
    output[mask]=255                            # 将 =1的值设置为 255
    return output

def devide_block_ostu( input, i_divided_num, j_divided_num ):
    '''
    将图片分块用 ostu算法处理 返回分割后的图像
    :param input:   输入灰度图，numpy数组
    :param i_devided_num:    i 轴等分数
    :param j_divided_num:    j 轴等分数
    :return:
    '''
    output = np.zeros(input.shape,dtype = np.uint8)
    block_height = input.shape[0]// i_divided_num
    block_width = input.shape[1]//j_divided_num
    #分块执行 ostu算法
    for i in range(i_divided_num):
        i_begin = i * block_height
        i_end = i_begin + block_height if i < i_divided_num - 1 else input.shape[0]  # 最后一次去全图 防止遗漏
        for j in range(j_divided_num):
            j_begin = j * block_width
            j_end = j_begin + block_width if j < j_divided_num - 1 else input.shape[1]  # 最后一次去全图 防止遗漏
            output[i_begin:i_end,j_begin:j_end] = otsu(  input[i_begin:i_end,j_begin:j_end] )
    return output

if __name__ =='__main__':
    BASE_PATH = os.path.dirname(os.path.abspath(__file__))
    RESULT_PATH = os.path.join(BASE_PATH, "result")
    if not os.path.exists(RESULT_PATH):
        os.mkdir(RESULT_PATH)
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--img', help="the path of the input img")
    parser.add_argument('--iNum', help='the num of in')
    parser.add_argument('--jNum', help='the num of jn')
    # parser.add_argument('--kernal_size', help='the size of the kernal')
    args = parser.parse_args()
    ################# 图片读取模块
    img_name = os.path.split(args.img)[-1]
    img_name, ext = os.path.splitext(img_name)
    input = cv.imread(args.img, flags=cv.IMREAD_GRAYSCALE)  # 读取灰度图片
    # input = cv.imread(args.img, flags=cv.IMREAD_COLOR) #读取rgb图片
    ########################## 处理模块
    output = devide_block_ostu(input,int(args.iNum),int(args.jNum))
    #########图片输出模块
    img_name = img_name + "_segmentation_" + str(args.iNum)+ "_" +  str(args.jNum)
    img_name = img_name + ext
    img_name = os.path.join(RESULT_PATH, img_name)
    cv.imwrite(img_name, output)