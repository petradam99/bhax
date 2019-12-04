/**
 * @brief Benchmarking Cognitive Abilities of the Brain with Computer Games
 *
 * @file BrainBThread.cpp
 * @author  Norbert Bátfai <nbatfai@gmail.com>
 * @version 6.0.1
 *
 * @section LICENSE
 *
 * Copyright (C) 2017, 2018 Norbert Bátfai, nbatfai@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * @section DESCRIPTION
 *
 */

#include "BrainBThread.h"
#include <cstdlib>
#include <ctime>

BrainBThread::BrainBThread ( int w, int h )
{

        dispShift = heroRectSize+heroRectSize/2;

        this->w = w - 3 * heroRectSize;
        this->h = h - 3 * heroRectSize;

        std::srand ( std::time ( 0 ) );

        Hero me ( this->w / 2 + 200.0 * std::rand() / ( RAND_MAX + 1.0 ) - 100,
                  this->h / 2 + 200.0 * std::rand() / ( RAND_MAX + 1.0 ) - 100, 255.0 * std::rand() / ( RAND_MAX + 1.0 ), 9 );

        Hero other1 ( this->w / 2 + 200.0 * std::rand() / ( RAND_MAX + 1.0 ) - 100,
                      this->h / 2 + 200.0 * std::rand() / ( RAND_MAX + 1.0 ) - 100, 255.0 * std::rand() / ( RAND_MAX + 1.0 ), 5, "NemesisR Entropy" );
        Hero other2 ( this->w / 2 + 200.0 * std::rand() / ( RAND_MAX + 1.0 ) - 100,
                      this->h / 2 + 200.0 * std::rand() / ( RAND_MAX + 1.0 ) - 100, 255.0 * std::rand() / ( RAND_MAX + 1.0 ), 3, "Shuvian Entropy" );
        Hero other4 ( this->w / 2 + 200.0 * std::rand() / ( RAND_MAX + 1.0 ) - 100,
                      this->h / 2 + 200.0 * std::rand() / ( RAND_MAX + 1.0 ) - 100, 255.0 * std::rand() / ( RAND_MAX + 1.0 ), 5, "RaptorX Entropy" );
        Hero other5 ( this->w / 2 + 200.0 * std::rand() / ( RAND_MAX + 1.0 ) - 100,
                      this->h / 2 + 200.0 * std::rand() / ( RAND_MAX + 1.0 ) - 100, 255.0 * std::rand() / ( RAND_MAX + 1.0 ), 7, "ZooM Entropy" );
        QTimer *timer = new QTimer(this);
        connect(timer, &QTimer::timeout,[=](  ) { this->doStuff(); });
        connect(this,SIGNAL(doStuff()),this, SLOT(updateCaption()));
        timer->setInterval(2000);
        timer->start();
        heroes.push_back ( me );
        heroes.push_back ( other1 );
        heroes.push_back ( other2 );
        heroes.push_back ( other4 );
        heroes.push_back ( other5 );

}

BrainBThread::~BrainBThread()
{

}

void BrainBThread::run()
{
        
        while ( time < endTime ) {

                QThread::msleep ( delay );
                
                if ( !paused ) {
                        ++time;
                        devel();

                }

                draw();

        }

        emit endAndStats ( endTime );

}

void BrainBThread::pause()
{

        paused = !paused;
        if ( paused ) {
                ++nofPaused;
        }

}
void BrainBThread::updateCaption(){
    for ( Hero & hero : heroes ){
        QDesktopWidget dw;
        if(hero.name=="Ifrit Entropy"){
            hero.randxy(dw.width(), dw.height(), ( h<w ) ?h/2:w/2);
        }
    }

}
void BrainBThread::set_paused ( bool p )
{

        if ( !paused && p ) {
                ++nofPaused;
        }

        paused = p;

}

void BrainBThread::set_color()
{
    

        for ( Hero & hero : heroes ) {
            if(hero.name=="Ifrit Entropy"){
            double r=std::rand()%255;
            double g=std::rand()%255;
            double b=std::rand()%255;
            cv::Scalar newCenter { r, g, b };
            cCenter1=newCenter;
            }
        }
    
}

void BrainBThread::set_color1()
{
             
            double r=std::rand()%255;
            double g=std::rand()%255;
            double b=std::rand()%255;
            cv::Scalar newCenter { r, g, b };
            cCenter=newCenter;

}

void BrainBThread::set_colorbg()
{
            double r=std::rand()%255;
            double g=std::rand()%255;
            double b=std::rand()%255;
            cv::Scalar newcBg { r, g, b };
            cBg=newcBg;
}