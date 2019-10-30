import cv2 as cv
import numpy as np
import os



def his_rgb_match(src,dst):

    src_model = src
    dst_model = dst
    res_model = np.zeros_like(dst)
    cdf_src = np.zeros((3,256))#sv直方图
    cdf_dst = np.zeros((3,256))
    cdf_res = np.zeros((3,256))

    kw = dict(bins=256, range=(0, 255), normed=True,density=True)
    for ch in range(3):
        hist_src, _ = np.histogram(src_model[:, :, ch], **kw)
        hist_dst, _ = np.histogram(dst_model[:, :, ch], **kw)
        cdf_src[ch] = np.cumsum(hist_src)
        cdf_dst[ch] = np.cumsum(hist_dst)
        index = np.searchsorted(cdf_src[ch], cdf_dst[ch], side='left')
        np.clip(index, 0, 255, out=index)
        res_model[:, :, ch] = index[dst_model[:, :, ch]]
        hist_res, _ = np.histogram(res_model[:, :, ch], **kw)
        cdf_res[ch] = np.cumsum(hist_res)

    result = res_model
    return result,hist_src,hist_res

#src为色调来源图
def his_hsv_match(src,dst):

    src_model = cv.cvtColor(src,cv.COLOR_BGR2HSV)
    dst_model = cv.cvtColor(dst,cv.COLOR_BGR2HSV)
    res_model = np.zeros_like(dst_model)
    cdf_src_h = np.zeros((1,180))#h直方图
    cdf_dst_h = np.zeros((1,180))
    cdf_res_h = np.zeros((1,180))

    cdf_src = np.zeros((2,256))#sv直方图
    cdf_dst = np.zeros((2,256))
    cdf_res = np.zeros((2,256))

    # kw = dict(bins=180, range=(0, 180), normed=True,density=True)
    # for ch in range(1):
    #     hist_src, _ = np.histogram(src_model[:, :, ch], **kw)
    #     hist_dst, _ = np.histogram(dst_model[:, :, ch], **kw)
    #     cdf_src_h[ch] = np.cumsum(hist_src)
    #     cdf_dst_h[ch] = np.cumsum(hist_dst)
    #     index = np.searchsorted(cdf_src_h[ch], cdf_dst_h[ch], side='left')
    #     np.clip(index, 0, 180, out=index)

    #     res_model[:, :, ch] = index[dst_model[:, :, ch]]
    #     hist_res, _ = np.histogram(res_model[:, :, ch], **kw)
    #     cdf_res_h[ch] = np.cumsum(hist_res)

    kw = dict(bins=256, range=(0, 255), normed=True,density=True)
    for ch in range(2):
        hist_src, _ = np.histogram(src_model[:, :, ch+1], **kw)
        hist_dst, _ = np.histogram(dst_model[:, :, ch+1], **kw)
        cdf_src[ch] = np.cumsum(hist_src)
        cdf_dst[ch] = np.cumsum(hist_dst)
        index = np.searchsorted(cdf_src[ch], cdf_dst[ch], side='left')
        np.clip(index, 0, 256, out=index)
        alpha=0.95
        res_model[:, :, ch+1] = alpha*index[dst_model[:, :, ch+1]]+(1-alpha)*dst_model[:, :, ch+1]
        hist_res, _ = np.histogram(res_model[:, :, ch+1], **kw)
        cdf_res[ch] = np.cumsum(hist_res)

    # res_model[:, :, 1]=dst_model[:, :, 1]
    res_model[:, :, 0]=dst_model[:, :, 0]
    result = cv.cvtColor(res_model,cv.COLOR_HSV2BGR)
    return result,hist_src,hist_res
def his_lab_match(src,dst):

    src_model = cv.cvtColor(src,cv.COLOR_BGR2Lab)
    dst_model = cv.cvtColor(dst,cv.COLOR_BGR2Lab)
    res_model = np.zeros_like(dst_model)
    cdf_src_h = np.zeros((1,100))#h直方图
    cdf_dst_h = np.zeros((1,100))
    cdf_res_h = np.zeros((1,100))

    cdf_src = np.zeros((2,256))#sv直方图
    cdf_dst = np.zeros((2,256))
    cdf_res = np.zeros((2,256))

    # kw = dict(bins=180, range=(0, 180), normed=True,density=True)
    # for ch in range(1):
    #     hist_src, _ = np.histogram(src_model[:, :, ch], **kw)
    #     hist_dst, _ = np.histogram(dst_model[:, :, ch], **kw)
    #     cdf_src_h[ch] = np.cumsum(hist_src)
    #     cdf_dst_h[ch] = np.cumsum(hist_dst)
    #     index = np.searchsorted(cdf_src_h[ch], cdf_dst_h[ch], side='left')
    #     np.clip(index, 0, 180, out=index)

    #     res_model[:, :, ch] = index[dst_model[:, :, ch]]
    #     hist_res, _ = np.histogram(res_model[:, :, ch], **kw)
    #     cdf_res_h[ch] = np.cumsum(hist_res)

    kw = dict(bins=256, range=(0, 255), normed=True,density=True)
    for ch in range(2):
        hist_src, _ = np.histogram(src_model[:, :, ch+1], **kw)
        hist_dst, _ = np.histogram(dst_model[:, :, ch+1], **kw)
        cdf_src[ch] = np.cumsum(hist_src)
        cdf_dst[ch] = np.cumsum(hist_dst)
        index = np.searchsorted(cdf_src[ch], cdf_dst[ch], side='left')
        np.clip(index, 0, 256, out=index)
        alpha=0.99
        res_model[:, :, ch+1] = alpha*index[dst_model[:, :, ch+1]]+(1-alpha)*dst_model[:, :, ch+1]
        hist_res, _ = np.histogram(res_model[:, :, ch+1], **kw)
        cdf_res[ch] = np.cumsum(hist_res)

    # res_model[:, :, 1]=dst_model[:, :, 1]
    res_model[:, :, 0]=dst_model[:, :, 0]
    result = cv.cvtColor(res_model,cv.COLOR_Lab2BGR)
    return result,hist_src,hist_res

def his_ycrcb_match(src,dst):
    theta1=0.8
    src_model = cv.cvtColor(src,cv.COLOR_BGR2YCR_CB)
    dst_model = cv.cvtColor(dst,cv.COLOR_BGR2YCR_CB)
    res_model = np.zeros_like(dst_model)

    cdf_src = np.zeros((3,256))#sv直方图
    cdf_dst = np.zeros((3,256))
    cdf_res = np.zeros((3,256))

    kw = dict(bins=256, range=(0, 255), normed=True,density=True)
    for ch in range(1,3):
        hist_src, _ = np.histogram(src_model[:, :, ch], **kw)
        hist_dst, _ = np.histogram(dst_model[:, :, ch], **kw)
        cdf_src[ch] = np.cumsum(hist_src)
        cdf_dst[ch] = np.cumsum(hist_dst)
        index = np.searchsorted(cdf_src[ch], cdf_dst[ch], side='left')
        np.clip(index, 0, 255, out=index)

        res_model[:, :, ch] = theta1*index[dst_model[:, :, ch]]+(1-theta1)*dst_model[:, :, ch]
        hist_res, _ = np.histogram(res_model[:, :, ch], **kw)
        cdf_res[ch] = np.cumsum(hist_res)

    theta2=0
    res_model[:, :, 0]=(1-theta2)*dst_model[:, :, 0]#+theta2*res_model[:, :, 0]

    result = cv.cvtColor(res_model,cv.COLOR_YCrCb2BGR)
    return result,hist_src,hist_res

def adjustV(src,res):
    hsv_res = cv.cvtColor(res, cv.COLOR_BGR2HSV)
    hsv_src = cv.cvtColor(src, cv.COLOR_BGR2HSV)
    mean_res=np.mean(hsv_res[:,:,2])
    mean_src=np.mean(hsv_src[:,:,2])
    offset=np.array(mean_src-mean_res)
    offset=offset.astype(np.int16)
    temp=hsv_res[:,:,2]
    temp=temp.astype(np.int16)
    temp+=offset
    np.clip(temp, 0, 255, out=temp)
    temp=temp.astype(np.uint8)
    hsv_res[:,:,2]=temp
    cv.cvtColor(hsv_res, cv.COLOR_HSV2BGR, res)
    return res

def hisEqulColor(img,ch):##直方图均衡
    ycrcb = cv.cvtColor(img, cv.COLOR_BGR2YCR_CB)
    channels = cv.split(ycrcb)
    cv.equalizeHist(channels[ch], channels[ch])
    cv.merge(channels, ycrcb)
    cv.cvtColor(ycrcb, cv.COLOR_YCR_CB2BGR, img)
    return img

def mergeHSV(res,dst):
    hsv_res = cv.cvtColor(res, cv.COLOR_BGR2HSV)
    hsv_dst = cv.cvtColor(dst, cv.COLOR_BGR2HSV)
    channels_res = cv.split(hsv_res)
    channels_dst = cv.split(hsv_dst)
    # cv.imshow('h',channels_dst[0])
    # cv.imshow('s',channels_dst[1])
    # cv.imshow('v',channels_dst[2])
    # cv.waitKey(0)
    channels_res[1]=channels_dst[1]
    cv.merge(channels_res, hsv_res)
    cv.cvtColor(hsv_res, cv.COLOR_HSV2BGR, res)
    return res

def mergeYCRCB(res,dst):
    hsv_res = cv.cvtColor(res, cv.COLOR_BGR2YCR_CB)
    hsv_dst = cv.cvtColor(dst, cv.COLOR_BGR2YCR_CB)
    channels_res = cv.split(hsv_res)
    channels_dst = cv.split(hsv_dst)
    cv.imshow('Y',channels_dst[0])
    cv.imshow('R',channels_dst[1])
    cv.imshow('B',channels_dst[2])
    cv.waitKey(0)
    # channels_res[2]=channels_dst[2]
    cv.merge(channels_res, hsv_res)
    cv.cvtColor(hsv_res, cv.COLOR_YCR_CB2BGR, res)
    return res

def  his_ycrcb_match_plus(src,dst):
    result,_,_= his_ycrcb_match(src,dst)
    result = adjustV(src, result)
    return result,src,dst

##=================================================================================
BASE_PATH = "D:/CodeMonkey/WORKSPACE/SEU-CS-LEARNING/SEU-CS-LEARNING/computerVision/the first"
RESULT_PATH = os.path.join(BASE_PATH,"result")
RESULT_PATH2 = os.path.join(BASE_PATH,"result2")
SRC_PATH = os.path.join(BASE_PATH,'src')
DST_PATH =os.path.join(BASE_PATH,'dst')

src_images = os.listdir(SRC_PATH)
dst_images = os.listdir(DST_PATH)

functions ={"rgb": his_rgb_match, "hsv":his_hsv_match,"lab":his_lab_match,"ycrcb":his_ycrcb_match,"ycrcb_p":his_ycrcb_match_plus}
# src 是 原图像 dst 是提供风格的图像
for dst in dst_images:
    ext = os.path.splitext(dst)[1]
    result_folder = os.path.join(RESULT_PATH,os.path.splitext(dst)[0])   # 文件夹名称
    if not os.path.exists(result_folder):
        os.mkdir(result_folder)
    dst_path = os.path.join(DST_PATH,dst)
    for src in src_images:
        result_folder2 = os.path.join(RESULT_PATH2,os.path.splitext(src)[0])
        if not os.path.exists(result_folder2):
            os.mkdir(result_folder2)
        src_path = os.path.join(SRC_PATH,src)
        for key in functions.keys():
            sub_result_folder = os.path.join( result_folder,key)
            sub_result_folder2 = os.path.join(result_folder2, key)
            if not os.path.exists(sub_result_folder):
                os.mkdir(sub_result_folder)
            if not os.path.exists(sub_result_folder2):
                os.mkdir(sub_result_folder2)
            result_dir = os.path.join(sub_result_folder,key+os.path.splitext(src)[0]+ext)

            result_dir2 = os.path.join(sub_result_folder2,key+dst)
            src_img = cv.imread(src_path)
            dst_img = cv.imread(dst_path)
            result_img,_,_ = functions[key](src_img,dst_img)
            cv.imwrite(result_dir,result_img)
            cv.imwrite(result_dir2, result_img)

# src = cv.imread('D:\\CodeMonkey\\WORKSPACE\\SEU-CS-LEARNING\\SEU-CS-LEARNING\\computerVision\\the first\\mamabuluo-1530409573-1.jpeg')
# dst = cv.imread('D:\\CodeMonkey\\WORKSPACE\\SEU-CS-LEARNING\\SEU-CS-LEARNING\\computerVision\\the first\\redimg.png')
#
# cv.imshow('source',src)
# # result,hist_src,hist_res = his_lab_match(src,dst)
# # # result,hist_src,hist_res = his_rgb_match(src,result)
# # # cv.imshow('BF_ADJUST',result)
# #
# # result=adjustV(src,result)
#
# # result,hist_src,hist_res = his_hsv_match(src,dst)
#
#
# # np.set_printoptions(precision=2,suppress=True)
# # print(hist_src)
# # print("================================")
# # print(hist_res)
#
# # result2,hist_src,hist_res = his_ycrcb_match(src,dst)
# # result2=adjustV(src,result2)
# # mergeHSV(result,dst)
# # cv.imshow('Lab',result)
# # cv.imshow('yrarb',result2)
#
# result,hist_src,hist_res =  his_rgb_match(src,dst)
# cv.imshow('his_rgb_match',result)
# cv.waitKey(0)


