/** 
 * @file	opencv_example.cpp
 * @version	0.0
 * @date	19-9-2019
 *
 * @brief	把常用的opencv函数及一些常用知识点进行一个总结与含括
 * 			毕竟是个含括文件所以其中的变量并没有很严格的命名,不过看得懂就好
 */
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <iostream>
#include <stdio.h>

using namespace std;
using namespace cv;

#define R_MAX 255
#define G_MAX 255
#define B_MAX 255

int R_val = 0, G_val = 0, B_val = 0;

/**
* @brief	滑条回调函数
* @param	int说明关联的值是int类型的
* @param	mat是传进来的用户自定义参数 是void*类型
* @note		用户自定义参数可以用C++的元组打包发过来
*			只要没有destroy这个窗口则这个bar会一直存在,只要动了滑条就会调用回调函数
*/
void bar_callback(int, void *mat)
{
	Mat img = (*(Mat *)mat).clone(); //创建一个img为传入参数的clone 可使得在img上画图不影响原来的图
	char text[20];
	sprintf(text, "R:%d G:%d B:%d", R_val, G_val, B_val);
	putText(img, text, Point(20, 20), FONT_HERSHEY_PLAIN, 2.0, Scalar(255, 0, 255)); //在图片上显示文字
	imshow("show", img);
	cout << R_val << " " << G_val << " " << B_val << endl; //打印三个通道的值
	waitKey(1);
}

/**
* @brief	鼠标回调函数
* @param	event：鼠标事件 详情见cv::MouseEventTypes
* @param	x,y：鼠标的位置
* @param	flags：鼠标事件标志位 详情见cv::MouseEventFlags
* @param	mat是传进来的用户自定义参数 是void*类型
* @note		用户自定义参数可以用C++的元组打包发过来
*			只要没有destroy这个窗口则这个事件会一直存在,只要点了鼠标就会调用回调函数
*/
void mouse_callback(int event, int x, int y, int flags, void *mat)
{
	if (event == CV_EVENT_LBUTTONDOWN) //判断是否是鼠标左键按下
	{
		Mat img = (*(Mat *)mat).clone(); //创建一个img为传入参数的clone 可使得在img上画图不影响原来的图
		Point pt = Point(x, y);
		char text[16];
		sprintf(text, "(%d,%d)", x, y);
		putText(img, text, pt, CV_FONT_HERSHEY_COMPLEX, 0.5, Scalar(255, 0, 255), 1); //在图片上显示文字
		printf("x=%d\ty=%d\t", x, y);												  //打印各种信息
		printf("b=%d\t", img.at<Vec3b>(pt)[0]);
		printf("g=%d\t", img.at<Vec3b>(pt)[1]);
		printf("r=%d\n", img.at<Vec3b>(pt)[2]);
		circle(img, pt, 2, Scalar(0, 0, 255), 2, 8); //在鼠标点击的地方画个圆
		imshow("show", img);
		waitKey(1);
	}
}

int main()
{
	/* 窗口的操作 */
	namedWindow("show");		   //创建名字为show的窗口
	cvMoveWindow("show", 2560, 0); //移动名字为show的窗口左上角到x为2560,y为0的这个地方

	/* 特定值图像的定义 */
	Mat E = Mat::eye(4, 4, CV_64FC1);   //创建一个4x4的单位矩阵既对角线全为1 单通道
	Mat Z = Mat::zeros(4, 4, CV_32FC1); //创建一个4x4的全为0的矩阵 单通道
	Mat O = Mat::ones(4, 4, CV_8UC3);   //创建一个4x4的全为1的矩阵 虽然是三通道但只有一个通道全为1

	/* 打印图像的值 */
	cout << E << endl;
	cout << Z << endl;
	cout << format(O, Formatter::FMT_PYTHON) << endl; //以python的格式输出图像
	O = O + 233;									  //可见只有第一个通道加了233变成234 直接数学操作只能操作到第一个通道
	cout << format(O, Formatter::FMT_PYTHON) << endl;

	/* 图像的定义 */
	Mat img_temp;													  //定义一个img_temp,默认指向的是CV_8UC1
	Mat img_8UC3(500, 500, CV_8UC3, Scalar(255, 255, 255));			  //创建一个500x500的8位3通道的 BGR 值都为255的图片,通道值类型uchar
	Mat img_16UC1(500, 500, CV_16UC1, 32768);						  //创建一个500x500的16位1通道的值都为32768的图片,通道值类型ushort,此类图片若需要存储则用png。jpg是不行的
	Mat img_16UC3 = Mat(500, 500, CV_16UC3, Scalar(65535, 32768, 0)); //Mat是个类所以可以调用它的构造器来创建

	/* 图像中绘制文字 */
	putText(img_16UC1, "img_16UC1", Point(100, 100), FONT_HERSHEY_PLAIN, 2.0, 65535, 2);	//在img_16UC1这个图片上显示"img_16UC1",字符左下角在(100,100),接着是字体,字体大小,颜色及粗细
	imshow("show", img_16UC1);																//在名字为show的窗口上显示这个图片
	while (char(waitKey(1)) != 'q');														//按q跳过

	putText(img_8UC3, "img_8UC3", Point(100, 100), FONT_HERSHEY_PLAIN, 2.0, Scalar(255, 0, 0), 2);	//在img_16UC1这个图片上显示"img_16UC1",字符左下角在(100,100),接着是字体,字体大小,颜色及粗细
	imshow("show", img_8UC3);																		//在名字为show的窗口上显示这个图片
	while (char(waitKey(1)) != 'q');																//按q跳过

	/* 图像的各种信息 */
	cout << "img_temp.type:" << img_temp.type() << " img_8UC3.type:" << img_8UC3.type() << endl;		   //打印图像类型 其中img_temp为8uc1对应0,img_8UC3为8uc3对应16 详情可以去看那个网站
	cout << "img_8UC3.cols:" << img_8UC3.cols << " img_8UC3.rows:" << img_8UC3.rows << endl;			   //打印img_8UC3的列与行 cols为列 rows为行 这里都是500
	cout << "img_8UC3.depth:" << img_8UC3.depth() << " img_8UC3.channels:" << img_8UC3.channels() << endl; //打印img_8UC3的图像深度与通道数 这里是8位深度对应0 通道数是3

	/* 图像的拷贝与复制 */
	Mat img_temp_ones = Mat::ones(1, 5, CV_8UC1);
	Mat img_temp_zeros = Mat::zeros(1, 5, CV_8UC1);

	img_temp = img_temp_ones;				  	//img_temp指向img_temp_ones所指的[1,1,1,1,1] 5个1
	img_temp_ones = Mat::ones(1, 4, CV_8UC1);	//把img_temp_ones指向[1,1,1,1] 4个1
	cout << img_temp << endl;				 	//可见img_temp指向的[1,1,1,1,1] 5个1 想想指针就知道了

	img_temp_ones.copyTo(img_temp);			 	//深拷贝 img_temp指向的地方的数据改成img_temp_ones所指的[1,1,1,1] 4个1  这里要注意的是若两个大小相同则不开新内存,若不同则开
	img_temp_ones = Mat::ones(1, 5, CV_8UC1);	//把img_temp_ones指向[1,1,1,1,1] 5个1
	cout << img_temp << endl;				 	//可见img_temp指向的[1,1,1,1] 4个1 原理跟上面的是一样的

	img_temp = img_temp_ones;					//img_temp指向img_temp_ones所指的[1,1,1,1,1] 5个1
	img_temp_ones = img_temp_ones + 233;		//img_temp_ones指向的内存的第一个通道所有值+233变成[234,234,234,234,234]
	cout << img_temp << endl;					//因为img_temp与img_temp_ones指向的是同一个东西所以img_temp也变成[234,234,234,234,234]

	img_temp = img_temp_ones.clone();			//clone是新开一块内存 与copyTo不同的是无论大小一不一致都新开一块内存 相同的是他们都是深拷贝！但copyTo更快
	img_temp_ones = img_temp_ones - 233;		//img_temp_ones指向的内存的第一个通道所有值-233变成[1,1,1,1,1]
	cout << img_temp << endl;					//因为img_temp是独立的另外一块内存所以是 [234,234,234,234,234]

	/* 图片的读取与存取 */
	img_temp = imread("C:/software/IMG/saber1.jpg");					//读取特定的图片,后面那个参数可选 代表以什么格式读进来 详情F12去看 默认是1
	imshow("show", img_temp);
	while (char(waitKey(1)) != 'q');

	img_temp = imread("C:/software/IMG/saber1.jpg", IMREAD_GRAYSCALE);	//黑白得读取一张图片 是单通道的
	imshow("show", img_temp);
	while (char(waitKey(1)) != 'q');

	img_temp = Mat(500, 500, CV_16UC3, Scalar(65535, 32768, 0));		//创建一个500x500的16位三通道的图片 复制BGR分别为65536,32768,0
	imshow("show", img_temp);
	imwrite("C:/software/IMG/test1.png", img_temp);						//jpg的写是没有超过8位的 所以还是用PNG比较好一点吧 这个函数还有一些参数但是应该用不上 若需要保存颜色不变则需要下面的convertTo函数
	while (char(waitKey(1)) != 'q');

	/* 图片的按轴对称与转置既横变竖 */
	flip(imread("C:/software/IMG/saber1.jpg"), img_temp, 0);	//0是按X轴转 1是按Y轴旋转 -1是两个都转
	imshow("show", img_temp);
	while (char(waitKey(1)) != 'q');

	flip(imread("C:/software/IMG/saber1.jpg"), img_temp, 1);	//0是按X轴转 1是按Y轴旋转 -1是两个都转
	imshow("show", img_temp);
	while (char(waitKey(1)) != 'q');

	flip(imread("C:/software/IMG/saber1.jpg"), img_temp, -1);	//0是按X轴转 1是按Y轴旋转 -1是两个都转
	imshow("show", img_temp);
	while (char(waitKey(1)) != 'q');

	transpose(imread("C:/software/IMG/saber1.jpg"), img_temp);	//转置既旋转90度
	imshow("show", img_temp);
	while (char(waitKey(1)) != 'q');

	/* 图片的仿射变换 */
	Mat rot_mat = getRotationMatrix2D(Point(img_temp.cols / 2, img_temp.rows / 2), 45, 2);	//得到旋转矩阵 第一个参数是旋转中心 第二个参数是旋转角度 第三个参数是放大几倍,可以是小数
	warpAffine(img_temp, img_temp, rot_mat, img_temp.size());							  	//输入仿射矩阵也就是上面的旋转矩阵 后面的size是生成的图面的大小 若知道两队三点则可用一个函数求出这个仿射矩阵 详情见百度
	imshow("show", img_temp);
	while (char(waitKey(1)) != 'q');

	/* 图像像素的访问 */
	img_temp = imread("C:/software/IMG/saber1.jpg", IMREAD_GRAYSCALE);	//黑白得读取一张图片 是单通道的
	cout << img_temp.at<uchar>(100, 100) << endl;					  	//黑白的只有一个通道所以只需要输入坐标即可

	img_temp = imread("C:/software/IMG/saber1.jpg");
	cout << img_temp.at<Vec3b>(100, 100)[0] << endl;					//三通道的所以一个点的类型是Vec3b,这里是3个uchar的组合,输入坐标之后还要取出vector中的某个通道值

	/* 滑条的使用 */
	namedWindow("bar_window");													  	//创建一个窗口bar_window
	cvMoveWindow("bar_window", 2100, 0);										  	//移动这个窗口
	createTrackbar("R_val", "bar_window", &R_val, R_MAX, bar_callback, &img_temp);	//在bar_window这个窗口创建名为R_val的滑条 滑条关联值是R_val 最大为R_MAX 回调函数句柄为bar_callback 传入参数img_temp
	createTrackbar("G_val", "bar_window", &G_val, G_MAX, bar_callback, &img_temp);	//														 默认最小为0					传入参数可以是一个打包好的元组
	createTrackbar("B_val", "bar_window", &B_val, B_MAX, bar_callback, &img_temp);
	while (char(waitKey(1)) != 'q');

	/* 鼠标的使用 */
	setMouseCallback("show", mouse_callback, &img_temp);							//在show这个窗口关联鼠标 mouse_callback是回调函数句柄 传入参数img_temp
	while (char(waitKey(1)) != 'q');

	/* 绘制一些图形 */
	img_temp = Mat(500, 720, CV_8UC3, Scalar(255, 0, 128));
	line(img_temp, Point(20, 40), Point(120, 140), Scalar(255, 0, 0), 3);					//绘制直线 第一个point是起点 第二个point是终点 scalar是调色板
	rectangle(img_temp, Point(150, 40), Point(250, 140), Scalar(0, 0, 255), -1);			//绘制长方形 第一个点是左上角 二个点是右下角 scalar是调色板
	circle(img_temp, Point(330, 90), 50, Scalar(0, 255, 0), -1);							//绘制圆 第一个参数是圆心 第二个参数是半径 scalar是调色板 后面的参数表示圆轮廓的大小,若为负数则表示填充
	circle(img_temp, Point(330, 90), 1, Scalar(0, 0, 255), 2);								//绘制圆心 半径是1 轮廓宽度是2
	ellipse(img_temp, Point(460, 90), Size(60, 40), 45, 0, 360, Scalar(255, 255, 0), 2);	//绘制椭圆 不常用所以放着先吧
	vector<Point> points;
	points.push_back(Point(540, 90));
	points.push_back(Point(580, 50));
	points.push_back(Point(600, 110));
	points.push_back(Point(530, 116));
	points.push_back(Point(612, 136));
	polylines(img_temp, points, true, Scalar(0, 255, 255), 2);		//绘制多边形轮廓 points是一个point的vector 接着是否是闭合 颜色 粗细
	vector<vector<Point> > vpoints;
	vpoints.push_back(points);
	fillPoly(img_temp, vpoints, Scalar(100, 168, 247), 8, 0);		//填充这一块多边形 第二个参数是个二维的vector的vector
	imshow("show", img_temp);
	while (char(waitKey(1)) != 'q');

	/* 图片数据类型转换 */
	img_temp = Mat(500, 500, CV_16UC3, Scalar(65535, 32768, 0));	//定义一个3通道的16位深度的图片并给BGR三个通道赋值
	imshow("show", img_temp);
	while (char(waitKey(1)) != 'q');
	img_temp.convertTo(img_temp, CV_8U, 255.0 / 65535, 0.0);		//转换成3位8通道的图片 第三个参数是尺度,也就是原图乘上这个比例,注意是小数 第四个参数是偏置 可见这个函数还可以用来改变对比度和亮度
	imshow("show", img_temp);
	while (char(waitKey(1)) != 'q');

	/* 图片转换颜色空间 */
	Mat gray_img, lab_img, hsv_img;
	img_temp = imread("C:/software/IMG/saber1.jpg");
	cvtColor(img_temp, gray_img, CV_BGR2GRAY);						//BGR转灰度图
	cvtColor(img_temp, lab_img, CV_BGR2Lab);						//BGR转换颜色空间到lab
	cvtColor(img_temp, hsv_img, CV_BGR2HSV);						//BGR转换颜色空间到HSV
	imshow("show", gray_img);
	while (char(waitKey(1)) != 'q');
	imshow("show", lab_img);
	while (char(waitKey(1)) != 'q');
	imshow("show", hsv_img);
	while (char(waitKey(1)) != 'q');

	/* 图片的滤波 */
	Mat img_show;
	boxFilter(img_temp, img_show, -1, Size(5, 5));					//方框滤波 第三个参数表示输出图像的深度 这里-1则用输入的 卷积核是全为1的5x5核 第六个参数默认为1表示归一化也就是均值滤波,若不为1则不均值
	imshow("show", img_show);
	while (char(waitKey(1)) != 'q');

	blur(img_temp, img_show, Size(5, 5));							//均值滤波 其实就是归一化的boxFilter
	imshow("show", img_show);
	while (char(waitKey(1)) != 'q');

	GaussianBlur(img_temp, img_show, Size(3, 3), 0, 0);				//高斯滤波 第四个参数是高斯核在x方向上的标准差 第五个是y方向上的
	imshow("show", img_show);
	while (char(waitKey(1)) != 'q');

	medianBlur(img_temp, img_show, 7);								//中值滤波 第三个参数也就是核的大小 它必须是奇数
	imshow("show", img_show);
	while (char(waitKey(1)) != 'q');

	bilateralFilter(img_temp, img_show, 25, 25 * 2, 25 / 2);		//双边滤波 可以保边 估计也用不到 用到了就百度就好了
	imshow("show", img_show);
	while (char(waitKey(1)) != 'q');

	/* 膨胀与腐蚀 */
	Mat element = getStructuringElement(MORPH_RECT, Size(15, 15));	//自定义的核 第一个参数是核的形状 这里用的是矩形 详情见MorphShapes
	dilate(img_temp, img_show, element);						  	//膨胀 也就是求局部最大值 亮的地方更亮
	imshow("show", img_show);
	while (char(waitKey(1)) != 'q');
	erode(img_temp, img_show, element);								//腐蚀 也就是求局部最小值 暗的地方更暗
	imshow("show", img_show);
	while (char(waitKey(1)) != 'q');

	/* 图像形态学运算 */
	morphologyEx(img_temp, img_show, MORPH_OPEN, element);			//开运算 先腐蚀后膨胀 用来消除小物体、在纤细点处分离物体、平滑较大物体的边界的同时并不明显改变其面积
	imshow("show", img_show);
	while (char(waitKey(1)) != 'q');

	morphologyEx(img_temp, img_show, MORPH_CLOSE, element);			//闭运算 先膨胀后腐蚀 排除小型黑洞(黑色区域)
	imshow("show", img_show);
	while (char(waitKey(1)) != 'q');

	morphologyEx(img_temp, img_show, MORPH_GRADIENT, element);		//形态学梯度 膨胀图与腐蚀图之差
	while (char(waitKey(1)) != 'q');

	morphologyEx(img_temp, img_show, MORPH_TOPHAT, element);		//顶帽运算 为原图与开运算图之差 用来分离比邻近点亮一些的斑块
	imshow("show", img_show);
	while (char(waitKey(1)) != 'q');

	morphologyEx(img_temp, img_show, MORPH_BLACKHAT, element);		//黑帽运算 闭运算图与原图之差 用来分离比邻近点暗一些的斑块
	imshow("show", img_show);
	while (char(waitKey(1)) != 'q');

	morphologyEx(img_temp, img_show, MORPH_ERODE, element);			//morphologyEx版腐蚀
	imshow("show", img_show);
	while (char(waitKey(1)) != 'q');

	morphologyEx(img_temp, img_show, MORPH_DILATE, element);		//morphologyEx版膨胀
	imshow("show", img_show);
	while (char(waitKey(1)) != 'q');

	/* 图像大小调整resize */
	img_temp = imread("C:/software/IMG/saber1.jpg");
	resize(img_temp, img_show, Size(img_temp.cols/2, img_temp.rows/2));
	imshow("show", img_show);
    while (char(waitKey(1)) != 'q');

    /* 图片通道分离与合成 */
    vector<Mat> channels;
    split(img_temp, channels);			//分离三个通道 对其他颜色空间也是一样的
    channels[2] = channels[2] + 100;	//对R通道做1加强 既图片变红
    merge(channels, img_show);			//合并
    imshow("show", img_show);
    while (char(waitKey(1)) != 'q');

    /* 图片区域选定 */
	img_show = img_temp(Rect(0, 0, img_temp.cols, img_temp.rows / 2));			//截取img_temp的(0,0)到(img_temp.cols, img_temp.rows / 2)为对角点的长方形区域
    imshow("show", img_show);
    while (char(waitKey(1)) != 'q');

    /* 图片覆盖与混合 */
    Mat samll_saber = imread("C:/software/IMG/small_saber.jpg");				//读取小一号的saber
    Mat img_rect = img_temp(Rect(0, 0, samll_saber.cols, samll_saber.rows));	//截取img_temp的左上角
    samll_saber.copyTo(img_rect);												//在左上角覆盖贴入小saber
    imshow("show", img_temp);
    while (char(waitKey(1)) != 'q');

    img_temp = imread("C:/software/IMG/saber1.jpg");							//因为上面被覆盖了所以重新读入
    img_rect = img_temp(Rect(0, 0, samll_saber.cols, samll_saber.rows));		//截取img_temp的左上角
    addWeighted(samll_saber, 0.5, img_rect, 0.5, 0.0, img_rect);				//融合的两幅图片必须是等大的 公式是0.5*src1+0.5*src2+偏置
    imshow("show", img_temp);
    while (char(waitKey(1)) != 'q');

    Mat add_text = imread("C:/software/IMG/add_text.jpg");
    addWeighted(samll_saber, 0.5, add_text, 0.5, 0.0, img_show);				//融合的两幅图片必须是等大的 公式是0.5*src1+0.5*src2+偏置
    imshow("show", img_show);
    while (char(waitKey(1)) != 'q');

    /* 图像对比度操作 */
    /* 第一种则是对一个个像素点一个个遍历操作 */
	img_show = Mat::zeros(img_temp.size(), img_temp.type());					//emmmmmmmm我也不知道为什么 反正这个size可以是个函数吧
    for (int i = 0; i < img_temp.rows; i++)
    {
        for (int j = 0; j < img_temp.cols; j++)
        {
            for (int k = 0; k < 3; k++)
            {
                img_show.at<Vec3b>(i, j)[k] = saturate_cast<uchar>(1.0 * (img_temp.at<Vec3b>(i, j)[k]) + 0.0);	//saturate_cast是为了溢出保护
            }
        }
    }

    /* 第二种则是直接用convertTo函数 */
    img_temp.convertTo(img_show, CV_8UC3, 1.0, 0.0);			//同样的乘上1加上0

	/* 基本阈值操作 */
	img_temp = imread("C:/software/IMG/array.png");
	imshow("show", img_temp);
	threshold(img_temp, img_show, 128, 255, THRESH_BINARY);		//128是设定的阈值 255是最大阈值 这里是大于128的置255小于等于128的置0 注意这里是对三个通道同时做阈值 THRESH_BINARY详情见ThresholdTypes
	imshow("dst", img_show);
	cvMoveWindow("dst",2560,700);
    while (char(waitKey(1)) != 'q');

    split(img_temp, channels);									//分离三个通道 对其他颜色空间也是一样的
    threshold(channels[2] - channels[0], img_show, 200, 255, THRESH_BINARY);
    imshow("dst", img_show);
    while (char(waitKey(1)) != 'q');
	destroyWindow("dst");

	/* 边缘检测 */
	img_temp = imread("C:/software/IMG/saber1.jpg");
	cvtColor(img_temp,img_show,CV_BGR2GRAY);					//先转成灰度图
	blur(img_show,img_show,Size(3,3));
	Canny(img_show, img_show, 10, 3 * 10, 3);					//第三个参数是第一个滞后性阈值 第四个参数是第二个滞后性阈值 推荐的高低阈值比在2:1到3:1之间 第五个是Sobel核的大小默认为3
	imshow("show", img_show);
	while (char(waitKey(1)) != 'q');


	/* 视频操作 */
	VideoCapture cap("C:/software/IMG/miaonei480p.mp4");											//打开特定地址的视频 若是使用摄像头则是0
	VideoWriter writer("C:/software/IMG/1.avi", CV_FOURCC('M', 'J', 'P', 'G'), 25, Size(852, 480));	//视频录制 录制在当前目录 25是fps

	if (!cap.isOpened()) //判断有没打开成功
	{
		return -1;
	}
	while (1)
	{
		cap >> img_temp;
		writer << img_temp;
		if (img_temp.empty()) //视频放完了则退出
		{
			break;
		}
		imshow("show", img_temp);
		char key = waitKey(30); //30ms一帧
		if (key == 27)			//若按下了ESC键则退出
		{
			break;
		}
		if (key == ' ') //若按下了空格键则暂停 再随便按一个键继续
		{
			key = waitKey(0);
		}
		if (key == 's') //若按下s键则保存当前帧
		{
			static int image_index = 1; //反正这里用imwrite这里不写了
			image_index++;
			cout << "save " << image_index << " done!";
		}
	}
	cap.release();
	writer.release();
	return 0;
}

/**
* @brief	点的转换函数
* @param	xyz：输入的点
* @retval	result：经转换之后的点
* @note		transfer_matrix为转移矩阵,与标定有关
*/
