import cv2 as cv
import os
import numpy as np

def resize_img(input,scale,mode,output_mode='same'):
    '''
    放大图像的函数,直接对整个图像进行放大
    :param input:  输入图像,注意输入图像是灰度图
    :param scale: 放大的尺度，是一个数组 [scale_h,scale_w] 或者说是 [scale_i,scale_j]
    :param mode:  插值方式有最近领和双线性
    :param output_mode  输出放肆
    :return:
    '''
    assert (mode in ['nearest','bilinear'])
    assert (output_mode in ['same','scaled'])
    input = np.array(input,dtype=np.uint8)
    input_shape = input.shape[0:2]
    output_shape = [int(input_shape[0]*scale[0]),int(input_shape[1]*scale[1])]  #计算输出尺寸
    output = np.zeros(output_shape,dtype = np.uint8)
    input =  np.pad(  input,((0,1),(0,1)),'constant')  # 填充防止越界
    for i in range(output_shape[0]):
        for j in range(output_shape[1]):
            #遍历输出图像的每一个像素
            if i%scale[0]==0 and j%scale[1]==0:
                output[i][j] = input[int(i/scale[0])][int(j/scale[1])]   #如果正好对应的话
            else:
                #求其所在方格左上角的点
                i_f = i/scale[0]
                j_f = j/scale[1]
                i_0 = int(np.floor(i_f))
                j_0 = int(np.floor(j_f))
                if mode=='nearest' :  
                    #如果是最近邻插值,如果在方格中心取左上角的点
                    if i_f - i_0 <=0.5:
                        offset_i=0
                    else:
                        offset_i = 1
                    if j_f - j_0 <=0.5:
                        offset_j=0
                    else:
                        offset_j = 1
                    output[i][j] = input[int(i_0+offset_i)][int(j_0+offset_j)]
                elif mode=='bilinear':
                    #双线性插值,根据双线性插值的原理 其  y = di*dj(c+a-d-b) + di*(d-a) + dj*(b-a) + a 其中 [a,b,c,d]分别是4个点的灰度值，a是左上角
                    #其余点按顺时针顺序
                    di = (i_f- i_0)
                    dj = (j_f - j_0)
                    a = int(input[i_0][j_0])
                    b = int(input[i_0][j_0+1])
                    c = int(input[i_0+1][j_0+1])
                    d = int(input[i_0+1][j_0])
                    output[i][j] = di*dj*(c+a-d-b) + di*(d-a) + dj*(b-a) + a
    # 输出
    if output_mode =='scaled':
        return np.array(output,dtype = np.uint8)
    elif output_mode =='same':
        #取中心点
        output_center = [s/2 for s in output_shape]
        i_begin = int(output_center[0]-0.5* input_shape[0] )
        j_begin =    int(output_center[1]-0.5* input_shape[1] )
        output = output[i_begin:i_begin+input_shape[0],j_begin:j_begin+input_shape[1]]
        return np.array(output, dtype=np.uint8)

if __name__ =='__main__':
    #主函数调用
    BASE_PATH = os.path.dirname(os.path.abspath(__file__))
    RESULT_PATH = os.path.join(BASE_PATH, "result")
    if not os.path.exists(RESULT_PATH):
        os.mkdir(RESULT_PATH)
    import argparse

    parser = argparse.ArgumentParser()
    parser.add_argument('--img', help="the path of the input img")
    parser.add_argument('--scale', help='the scale(>=1) ')
    parser.add_argument('--mode', help='insert mode')
    parser.add_argument('--output', help='output_mode')
    args = parser.parse_args()
    # 获取图片名称
    img_name = os.path.split(args.img)[-1]
    img_name, ext = os.path.splitext(img_name)
    ext = '.bmp'   #用 .bmp格式输出
    input = cv.imread(args.img, flags=cv.IMREAD_GRAYSCALE)
    if args.output:
        img_name = img_name + "_" + str(args.scale) + "_" + args.mode +'_'+args.output+ ext
        output = resize_img(input, [float(args.scale),float(args.scale)],args.mode,args.output )
    else:
        img_name = img_name + "_" + str(args.scale) + "_" + args.mode +'_same'+ ext
        output = resize_img(input, [float(args.scale), float(args.scale)], args.mode)
    img_name = os.path.join(RESULT_PATH, img_name)
    cv.imwrite(img_name, output)