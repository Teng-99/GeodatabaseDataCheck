// database.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include<fstream>
#include"SHAPEFIL.h"
using namespace std;
//快速排斥实验
bool IsIntersec(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
    return max(x1, x2) < min(x3, x4) || max(x3, x4) < min(x1, x2) || max(y1, y2) < min(y3, y4) || max(y3, y4) < min(y1, y2);
}
//跨立实验
bool cross(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4)
{
    return ((x1 - x3) * (y4 - y3) - (y1 - y3) * (x3 - x4)) * ((x2 - x3) * (y4 - y3) - (y2 - y3) * (x4 - x3)) < 0 && ((x3 - x1) * (y2 - y1) - (y3 - y1) * (x2 - x1)) * ((x4 - x1) * (y2 - y1) - (y4 - y1) * (x2 - x1)) < 0;
}



int main()
{
    _SHAPEFILE_H_INCLUDED::SHPHandle SHP = SHPOpen(".\\data\\2021testdata","rb");
    //DBFHandle DBF = DBFOpen(".\\data\\2021testdata", "rb");
    //cout.precision(12);
    int n = 0;
    double threshold = 5.0;
    if (SHP)
    {
        int nRecord = SHP->nRecords;
        for (int i = 0; i < nRecord; i++)
        {
            SHPObject* obj = SHPReadObject(SHP, i);
            int nVertices = obj->nVertices;
            if ((obj->padfX[0] - obj->padfX[nVertices - 1]) > threshold||(obj->padfY[0] - obj->padfY[nVertices - 1]))
            {
                cout << i << "首尾不相接" << endl;
                n++;
            }

            for (int j = 0; j < nVertices; j++)
            {
                if (j <= 2)
                    continue;
                for (int s = 0; s < j-1; s++) {
                    if (IsIntersec(obj->padfX[s], obj->padfY[s], obj->padfX[s + 1], obj->padfY[s + 1], obj->padfX[j], obj->padfY[j], obj->padfX[j - 1], obj->padfY[j - 1]))
                        continue;
                    if (cross(obj->padfX[s], obj->padfY[s], obj->padfX[s + 1], obj->padfY[s + 1], obj->padfX[j], obj->padfY[j], obj->padfX[j - 1], obj->padfY[j - 1]))
                    {
                        cout << "多边形" << i << "出现线段相交冲突,位于线段("<< s<<","<<s+1<<")和("<<j-1<<","<<j<<")处" << endl;
                        break;
                    }
                }
                    
            }
            
                

        }
    }
    else
    {
        cout << "File not exists!" << endl;
    }
    cout << "在阈值" << threshold << "下共有" << n << "个多边形首尾不相接" << endl;
    SHPClose(SHP);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
