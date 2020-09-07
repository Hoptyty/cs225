#include "maze.h"

SquareMaze::SquareMaze()
{

}

void SquareMaze::makeMaze( int width, int height )
{
    long n = width * height;
    DisjointSets myD;
    //myD.addelements(n);
    for (int i = 0; i < n; i++)
        myD.addelements(1);
    myWidth = width;
    myHeight = height;
    for (long i = 0; i < n; i++) {
        rightWall.push_back(true);
        downWall.push_back(true);
    }
    long count = 0;
    std::vector< long > mazeMaker1;
    std::vector< long > mazeMaker2;
    for (long i = 0; i < n; i++) {
        mazeMaker1.push_back(i);
        mazeMaker2.push_back(i);
    }
    while(count != n - 1) {
        //std::cout<<count<<endl;
        //count++;
        int rod = rand() % 2;
        //if (rod == 1)
        //    counter++;
        if(rod == 0 || mazeMaker2.empty()) {
            long long myIdx = rand() % mazeMaker1.size();
            //std::cout<<myIdx<<endl;
            long long i = mazeMaker1[myIdx];
            if(i % width < width - 1)
                if((myD.find(i) != myD.find(i + 1))) {
                    myD.setunion(i, i + 1);
                    rightWall[i] = false;
                    count++;
                }
            std::swap(mazeMaker1.back(), mazeMaker1[myIdx]);
            mazeMaker1.pop_back();
                
        }
        if(rod == 1 || mazeMaker1.empty()) {
            long long myIdx2 = rand() % mazeMaker2.size();
            long long j = mazeMaker2[myIdx2];
            if((j / width) < height - 1)
                if((myD.find(j) != myD.find(j + width))) {
                    myD.setunion(j, j + width);
                    downWall[j] = false;
                    count++;
                }
            std::swap(mazeMaker2.back(), mazeMaker2[myIdx2]);
            mazeMaker2.pop_back();
        }
    }
    
    /*
    for (int i = 0; i < n; i++) {
        if(i % width != width - 1) {
            int exists = rand() % 2;
            if(exists == 0 && (myD.find(i) != myD.find(i + 1))) {
                rightWall[i] = false;
                myD.setunion(i, i + 1);
                count++;
            }
        }
    }
    for (int i = 0; i< n; i++) {
        if(i / width != height - 1) {
            int exists = rand() % 2;
            if(exists == 0 && (myD.find(i) != myD.find(i + width))) {
                downWall[i] = false;
                myD.setunion(i, i + width);
                count++;
                if(count == n - 1)
                    break;
            }
        }
    }
    */
    /*
    while(count != n - 1) {
        int h = rand() % height - 1;
        for (int i = 0; i < width - 1; i++) {
            if(myD.find(h * width + i) != myD.find(h * width + i + 1)) {
                rightWall[h * width + i] = false;
                myD.setunion(h*width + i, h*width + i + 1);
                count++;
            }
            if(myD.find(h * width + i) != myD.find(h * width + i + width)) {
                downWall[h * width + i] = false;
                myD.setunion(h*width + i, h*width + i + width);
                count++;
            }
        }
    }
    */
}

bool SquareMaze::canTravel( int x, int y, int dir ) const
{
    if(dir == 0)
        return !rightWall[(long)(x + y * myWidth)];
    if(dir == 1)
        return !downWall[(long)(x + y * myWidth)];
    if(dir == 2) {
        if(x == 0)
            return false;
        return !rightWall[(long)(x + y * myWidth - 1)];
    }
        if(y == 0)
            return false;
        return !downWall[(long)(x + y * myWidth - myWidth)];
}

void SquareMaze::setWall( int x, int y, int dir, bool exists )
{
    if(dir == 0)
        rightWall[(long)(x + y * myWidth)] = exists;
    if(dir == 1)
        downWall[(long)(x + y * myWidth)] = exists;

}

std::vector< int > SquareMaze::solveMaze()
{
    std::vector< int > mySolution;
    std::vector< int > lengths;
    std::vector< int > position;
    lengths.push_back(0);
    int n = myWidth * myHeight;
    for (int i = 0; i < n; i++)
        position.push_back(-1);
    for (int i = 1; i < n; i++)
        lengths.push_back(-1);
    std::queue< int > myX;
    std::queue< int > myY;
    myX.push(0);
    myY.push(0);
    while(!myX.empty()) {
        int x = myX.front();
        int y = myY.front();
        myX.pop();
        myY.pop();
        int i = x + y * myWidth;
        if(!rightWall[i] && lengths[i + 1] < 0) {
            myX.push(x + 1);
            myY.push(y);
            lengths[i + 1] = lengths[i] + 1;
            position[i + 1] = 0;
        }
        if(!downWall[i] && lengths[i + myWidth] < 0) {
            myX.push(x);
            myY.push(y + 1);
            lengths[i + myWidth] = lengths[i] + 1;
            position[i + myWidth] = 1;
        }
        if(x != 0 && !rightWall[i - 1] && lengths[i - 1] < 0) {
            myX.push(x - 1);
            myY.push(y);
            lengths[i - 1] = lengths[i] + 1;
            position[i - 1] = 2;
        }
        if(y != 0 && !downWall[i - myWidth] && lengths[i - myWidth] < 0) {
            myX.push(x);
            myY.push(y - 1);
            lengths[i - myWidth] = lengths[i] + 1;
            position[i - myWidth] = 3;
        }
    }
    
    int max = n - myWidth;
    for (int j = n - myWidth + 1; j < n; j++)
        if(lengths[j] > lengths[max])
            max = j;
    std::vector< int > reverse;
    while(position[max] != -1) {
        if(position[max] == 0) {
            max = max - 1;
            reverse.push_back(0);
        }
        if(position[max] == 1) {
            max = max - myWidth;
            reverse.push_back(1);
        }
        if(position[max] == 2) {
            max = max + 1;
            reverse.push_back(2);
        }
        if(position[max] == 3) {
            max = max + myWidth;
            reverse.push_back(3);
        }
    }
    /*
    std::vector< int > reverse;
    while(lengths[max] != 0) {
        if(max % myWidth != 0)
            if(lengths[max - 1] == lengths[max] - 1) {
            max = max - 1;
            reverse.push_back(0);
        }
        if(max >= myWidth)
            if(lengths[max - myWidth] == lengths[max] - 1) {
                max = max - myWidth;
                reverse.push_back(1);
            }
        if(max % myWidth != myWidth - 1)
            if(lengths[max + 1] == lengths[max] - 1) {
                max = max + 1;
                reverse.push_back(2);
            }
        if(max >= n - myWidth)
            if(lengths[max + myWidth] == lengths[max] - 1) {
                max = max + myWidth;
                reverse.push_back(3);
            }
    }
    */
    while(!reverse.empty()) {
        int temp = reverse.back();
        reverse.pop_back();
        mySolution.push_back(temp);
    }
    
    return mySolution;
}

PNG * SquareMaze::drawMaze() const
{
    PNG * myMaze = new PNG(myWidth * 10 + 1, myHeight * 10 + 1);
    for (size_t i = 0; i < (size_t)myHeight * 10; i++) {
        (*myMaze)(0, i)->red = 0;
        (*myMaze)(0, i)->green = 0;
        (*myMaze)(0, i)->blue = 0;
    }
    for (size_t i = 10; i < (size_t)myWidth * 10; i++) {
        (*myMaze)(i, 0)->red = 0;
        (*myMaze)(i, 0)->green = 0;
        (*myMaze)(i, 0)->blue = 0;
    }
    for (size_t x = 0; x < (size_t)myWidth; x++)
        for (size_t y = 0; y < (size_t)myHeight; y++) {
            if(rightWall[x + y * myWidth])
                for (size_t k = 0; k < 11; k++) {
                    (*myMaze)((x + 1) * 10, y * 10 + k)->red = 0;
                    (*myMaze)((x + 1) * 10, y * 10 + k)->green = 0;
                    (*myMaze)((x + 1) * 10, y * 10 + k)->blue = 0;
                }
            if(downWall[x + y * myWidth])
                for (size_t k = 0; k < 11; k++) {
                    (*myMaze)(x * 10 + k, (y + 1) * 10)->red = 0;
                    (*myMaze)(x * 10 + k, (y + 1) * 10)->green = 0;
                    (*myMaze)(x * 10 + k, (y + 1) * 10)->blue = 0;
                }
        }
    return myMaze;
}

PNG * SquareMaze::drawMazeWithSolution()
{
    PNG * myMaze = drawMaze();
    std::vector< int > mySolution = solveMaze();
    size_t myX = 5;
    size_t myY = 5;
    for (int i = 0; i < (int)mySolution.size(); i++) {
        if(mySolution[i] == 0) {
            for (size_t i = 0; i < 11; i++) {
                (*myMaze)(myX + i, myY)->green = 0;
                (*myMaze)(myX + i, myY)->blue = 0;
            }
            myX += 10;
        }
        if(mySolution[i] == 1) {
            for (size_t i = 0; i < 11; i++) {
                (*myMaze)(myX, myY + i)->green = 0;
                (*myMaze)(myX, myY + i)->blue = 0;
            }
            myY += 10;
        }
        if(mySolution[i] == 2) {
            for (size_t i = 0; i < 11; i++) {
                (*myMaze)(myX - i, myY)->green = 0;
                (*myMaze)(myX - i, myY)->blue = 0;
            }
            myX -= 10;
        }
        if(mySolution[i] == 3) {
            for (size_t i = 0; i < 11; i++) {
                (*myMaze)(myX, myY - i)->green = 0;
                (*myMaze)(myX, myY - i)->blue = 0;
            }
            myY -= 10;
        }
    }
    int x = ( myX - 5) / 10;
    int y = ( myY - 5) / 10;
    for (size_t k = 1; k < 10; k++) {
        (*myMaze)(x * 10 + k, (y + 1) * 10)->red = 255;
        (*myMaze)(x * 10 + k, (y + 1) * 10)->green = 255;
        (*myMaze)(x * 10 + k, (y + 1) * 10)->blue = 255;
    }
    return myMaze;
}


