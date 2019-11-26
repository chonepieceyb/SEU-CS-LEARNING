import numpy as np
import cv2 as cv
import matplotlib.pyplot as plt
import os
def gamma_transformation(input,gamma,c):
    '''

    :param input: 输入图片为256灰度图
    :param gamma: gamma校正的参数
    :param c:     gamma校正的常数
    :return:
    '''
    input = np.array(input,dtype=np.float32)
    #对输入进行归一化归到（0，1）
    input = input/255            # 映射到[0,1]上
    input = np.power(input,gamma) #计算 r^gamma
    input = c* input              #计算 c*r^gamma
    #反映射
    output = input*(255/c)
    output = np.array(output,dtype= np.int32)
    return output

def plot_hism(input,name):
    '''
    统计输入的直方图并打印，输出的直方图不进行归一化
    '''
    input = np.array(input,dtype= np.int32)
    input = input.flatten()
    plt.figure(name)
    plt.xlabel('level')
    plt.ylabel("frequence")
    n,bins,patches = plt.hist(input,bins=128,density=1)
    plt.show()

if __name__ =='__main__':
    BASE_PATH = os.path.dirname(os.path.abspath(__file__))
    RESULT_PATH = os.path.join(BASE_PATH,"result")
    if not os.path.exists(RESULT_PATH):
        os.mkdir(RESULT_PATH)
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--img',help="the path of the input img")
    parser.add_argument('--gamma',help='the param of gamma transformation')
    parser.add_argument('--c', help='the param of gamma transformation')
    args = parser.parse_args()
    #获取图片名称
    img_name = os.path.split(args.img)[-1]
    img_name, ext = os.path.splitext(img_name)
    input = cv.imread(args.img,flags=cv.IMREAD_GRAYSCALE)
    plot_hism(input, img_name+"_before_gamma")
    output = gamma_transformation(input,float(args.gamma),float(args.c))
    img_name = img_name+"_"+str(args.gamma)+"_"+str(args.c)
    plot_hism(output,img_name)  # 打印直方图
    img_name = img_name+ext
    img_name = os.path.join(RESULT_PATH,img_name)
    cv.imwrite(img_name,output)
