import cv2 as cv
import os
import numpy as np

def sift_feature_extract(input,show=True,window='result'):
    '''
    :param input: 输入的RGB彩色图片
    :return: 将特征点标记在原图像上的output
    '''
    #定义sift
    sift = cv.xfeatures2d.SIFT_create()
    keypoints, descripter = sift.detectAndCompute(input,None)
    flags = cv.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS
    output = cv.drawKeypoints(input, keypoints, flags)
    if show:
        cv.imshow(window,output)
        cv.waitKey(0)
        #cv.destroyAllWindows()
    return output

def show_compare(input1, input2, img_name):
    img1 = cv.imread(input1)
    img2 = cv.imread(input2)
    g1 = cv.cvtColor(img1, cv.COLOR_BGR2GRAY)
    g2 = cv.cvtColor(img2, cv.COLOR_BGR2GRAY)
    sift = cv.xfeatures2d.SIFT_create()
    match = cv.FlannBasedMatcher(dict(algorithm =2, trees =1), {})
    kp1, de1 = sift.detectAndCompute(g1,None)
    kp2, de2 = sift.detectAndCompute(g2,None)
    m = match.knnMatch(de1, de2, 2)
    m = sorted(m,key = lambda x:x[0].distance)
    ok = [m1 for (m1, m2) in m if m1.distance < 0.7 * m2.distance]
    med = cv.drawMatches(img1, kp1, img2, kp2, ok, None)

    BASE_PATH = os.path.dirname(os.path.abspath(__file__))
    RESULT_PATH = os.path.join(BASE_PATH, "compare_result") # 输出文件夹
    if not os.path.exists(RESULT_PATH):
        os.mkdir(RESULT_PATH)
    cv.imwrite(img_name, med)
    cv.imshow('result',med)
    cv.waitKey(0)
    return

if __name__ =='__main__':
    BASE_PATH = os.path.dirname(os.path.abspath(__file__))
    RESULT_PATH = os.path.join(BASE_PATH, "result") # 输出文件夹
    if not os.path.exists(RESULT_PATH):
        os.mkdir(RESULT_PATH)
    import argparse
    parser = argparse.ArgumentParser()
    parser.add_argument('--img', help="the path of the input img")
    parser.add_argument('--command' )     # 命令有两种 e 提取特征并保存， c 特征匹配
    parser.add_argument('--mode')                       #模式 有 'blur' 'rotate' 'light' 'scale' 'sift'
    parser.add_argument('--option1')
    parser.add_argument('--option2')
    args = parser.parse_args()
##### 读取图片 #############
    img_name = os.path.split(args.img)[-1]
    img_name, ext = os.path.splitext(img_name)
    input = cv.imread(args.img, flags=cv.IMREAD_COLOR)
    temp = input
######处理模块###########
    #图像扰动
    if args.mode:
        commands =['blur','rotate','light','scale','shift']
        assert(args.mode in commands )
        if args.mode == 'blur':
            if args.option1:
                input = cv.blur(input,(int(args.option1),int(args.option1)))         #具体模糊参数需要改代码
                img_name = img_name + "_blur_"+args.option1
            else:
                input = cv.blur(input, (5,5))
                img_name = img_name +"_blur_5"
        elif args.mode =='rotate':
            h,w = input.shape[:2]    # 宽高
            center = (w // 2, h // 2) # 旋转中心
            if args.option1:
                R_M = cv.getRotationMatrix2D(center, float(args.option1), 1.0) #生成旋转矩阵 参数1 表示旋转中心，2 表示旋转角度 （从逆时针开始） 3表示旋转后的大小 1表示和原图相同
                print(R_M)
                img_name = img_name + "_rotate_" + args.option1
            else:
                R_M = cv.getRotationMatrix2D(center,45, 1.0)   #默认旋转45度
                img_name = img_name + "_rotate_45"
            input = cv.warpAffine(input, R_M, (w, h))
        elif args.mode =='light':
            # 采用 公式 g = a*f + b   参数 a 对应 option1 参数 b 对应 option2
             input = np.array(input)
             if args.option1 and args.option2:
                 input = float(args.option1)*input +int(args.option2)
                 img_name = img_name + "_light_" + args.option1 + '_'+args.option2
             else:
                 input =  3.0*input + np.uint8(20)   #默认值
                 img_name = img_name + "_light_3_20"
             # 约束到[0,255]
             input = np.clip(input, 0, 255)
             input = np.array(input,dtype=np.uint8)
        elif args.mode =='scale':
            scale = 0.8
            h, w = input.shape[:2]
            if args.option1:
                scale = float(args.option1)
                img_name = img_name + "_scale_"+args.option1
            else:
                img_name = img_name + "_scale_0.8"
            input = cv.resize(input, (int(w * scale), int(h * scale)), interpolation=cv.INTER_LINEAR)
        elif args.mode =='shift':
            h, w = input.shape[:2]
            shift_x =50
            shift_y=50
            if args.option1 and args.option2:
                shift_x =int(args.option1)
                shift_y = int(args.option2)
                img_name = img_name + "_shift_" + args.option1+"_"+args.option2
            else:
                img_name = img_name + "_shift_50_50"
            M_SHIFT = np.float32(
                [
                [1,0,shift_x],
                [0,1,shift_y]
                 ]
            )
            input=cv.warpAffine(input, M_SHIFT , (w, h))

    #特征匹配模块
    assert(args.command in ['e','c'])
    if args.command =='e': 
        #特征提取
        temp = sift_feature_extract(temp ,True,'original')		
        output = sift_feature_extract(input, True)
        img_name = img_name + "_sift_feature"
    else:
        output = input
########保存图片################
    img_name = img_name + ext
    img_name = os.path.join(RESULT_PATH, img_name)
    cv.imwrite(img_name, output)
    if args.command=='c':  
        #如果需要对比的话
        img_name = img_name
        output_dir,ext = os.path.splitext(img_name)
        output_dir = output_dir +"_compare" + ext
        show_compare(args.img,img_name,output_dir)
