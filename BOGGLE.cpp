#include<stdio.h>
#include<string>
#include<vector>
#include<cassert>
using namespace std;
const int dx[8]={-1,-1,-1,1,1,1,0,0};
const int dy[8]={-1,0,1,-1,0,1,-1,1};
/* 5X5의 보글 게임 판의 해당 위치에서 주어진 단어가 시작하는지를 반환 */
class Boggle {
	public:
	// 게임판의 정보를 저장한다
	vector<string> board;

    bool hasWord(int y,int x,const string& word)
    {
        // 기저 사례 1: 시작 위치가 범위 밖이면 무조건 실패
        if((y<0 || x<0) || (y>=5 || x>=5)) /* 시작 위치가 범위 밖이면 실패 */
            return false;
        if(board[y][x]!=word[0]) /* 첫 글자가 일치하지 않으면 실패 */
            return false;
        if(word.size()==1) /* 단어 길이가 1이면 성공 */
            return true;
        for(int direction=0;direction<8;++direction)
        {
            int nextY=y+dy[direction], nextX=x+dx[direction]; /* 다음 칸이 범위 안에 있는지,첫 글자는 일치하는지 확인할 필요가 없다 */
            if(hasWord(nextY,nextX,word.substr(1)))
                return true;
        }
        return false;
    }

    void run()
	{
		board.push_back("URLPM");
		board.push_back("XPRET");
		board.push_back("GIAET");
		board.push_back("XTNZY");
		board.push_back("HOQRS");
        /* 여기까지 게임판이 들어가지는 과정입니다. */
		assert(hasWord(1, 1, "PRETTY"));
		assert(hasWord(2, 0, "GIRL"));
		assert(hasWord(4, 0, "HONEY"));
		assert(!hasWord(1, 1, "PRETTMY"));
		assert(!hasWord(2, 0, "GIRAL"));
        /* 오류가 발생하는 지 확인하는 코드입니다.  */
	}
};
int main()
{
    Boggle().run(); /* Boogle() 이라는 클래스 안에서 run이라는 함수를 실행 */
    printf("All Tests Pass");
}