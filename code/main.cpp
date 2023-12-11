#include <ctime>
#include <cstdlib>
#include <iomanip>
#include "Relationship.hpp"

using namespace std; using namespace SocialNet;

#define BRACKET_LEN 44
//输出边框
void output_bracket(std::ostream& os){
    for(int i=0;i!=BRACKET_LEN;++i){
        os << '#';
    }
    os << '\n'; return;
}

const string _Data = "data.txt";
const string output = "output.txt";
const string input = "sample.txt";
const string dot = "。";
const string comma = "，";

int main(int argc,char** argv){
    //load from data.txt
    Relationship r;
    //timer
    time_t begin, end;
    try{
        r.load(_Data);
    }
    catch(std::domain_error e){
        cout << "无法打开文件" << _Data << ",终止" << endl;
        return 0;
    }

    //get input and generate output.
    std::ofstream fout(output.c_str());
    std::ifstream fin(input.c_str());
    if(!fin.is_open()){
        cout << "无法打开文件" << input << ",终止" << endl;
        return 0;
    }

    //part 1: direct and indirect friends count.
    int N, temp;
    int a, b;
    fin >> N;
    time(&begin);
    for(int i=0;i!=N;++i){
        fin >> temp;
        try{
            a = r.numOfFriend(temp);
        }
        catch(domain_error e){
            fout << "用户" << temp << "的信息!" << endl;
            continue;
        }
        fout << "用户" << temp << "的直接朋友数量为" << a << 
            "，间接朋友数量为" << r.numOfSubFriend(temp) << dot << endl;
    }
    time(&end);
    output_bracket(fout);
    cout << "直接朋友数量,间接朋友数量计算完成,用时" << difftime(end,begin)  << "s." << endl;

    //part 2: social distance calculation.
    fin >> N;
    time(&begin);
    for(int i=0;i!=N;++i){
        fin >> a >> b;
        fout << "用户" << a << "和用户" << b << "的最短社交距离为" << r.distanceOf(a,b) << dot << endl;
    }
    time(&end);
    output_bracket(fout);
    cout << "最短社交距离计算完成,用时" << difftime(end,begin)  << "s." << endl;

    //part 3: find the super user.
    time(&begin);
    vector<int> res = r.superUsers();
    fout << "网络中的“超级连接者”为用户" << res[0];
    for(size_t i=1;i!=res.size();++i){
        fout << ',' << res[i];
    }
    fout << dot << endl;
    time(&end);
    output_bracket(fout);
    cout << "所有超级用户查找完成,用时" << difftime(end,begin)  << "s." << endl;

    //part 4: 高级要求a的测试
    time(&begin);
    fout << "网络的平均聚集系数为" << setiosflags(ios::fixed) << setprecision(2) << r.clusteringCoefficient();
    fout << "，网络中朋友三角的数量为" << r.triangles() << dot << endl;
    time(&end);
    output_bracket(fout);
    cout << "高级要求a运算完成,用时" << difftime(end,begin)  << "s." << endl;

    //part 5: 高级要求b的测试
    fin >> N;
    time(&begin);
    for(int i=0;i!=N;++i){
        fin >> a;
        res = r.recommodations(a);
        fout << "向用户" << a << "推荐" << res[0];
        for(size_t i=1;i!=res.size();++i){
            fout << comma << res[i];
        }
        fout << dot << endl;
    } 
    time(&end);
    output_bracket(fout);
    cout << "高级要求b运算完成,用时" << difftime(end,begin)  << "s." << endl;

    //收尾工作
    fout.close();
    fin.close();
    return 0;
}