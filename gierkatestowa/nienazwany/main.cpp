#include <iostream>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <time.h>

int N=33,M=33;
int roz=16;
int w = roz*N;
int h = roz*M;
int kier, num = 2, najw = 2;
bool gra = 1;

struct Gracz
{
    int x,y;
}  s[100];

struct Punkt
{
    int x,y;
} f;

struct Duszek
{
    int x,y;
} wrr, wrr2;

struct Mur
{
    int x,y;
} mu[81];

int los()
{
    int a = rand()%(N-1);
    if(a%4)
            if ( s[0].x == a || s[0].y == a )
                los();
            else return a;
    else los();
}

void start()
{
    num = 2;
    kier = 0;
    s[0].x = 2;
    s[0].y = 0;
    f.x=los();  f.y=los();
    wrr.x=los(); wrr.y=los();
    wrr2.x=los(); wrr2.y=los();
}

void koniec()
{
    std::cout << "koniec gry, porazka" << std::endl << "twoj wynik : " << najw << std::endl;
    gra = 0;
}

void Tick()
 {
    for (int i=num;i>0;--i)
     {
        s[i].x=s[i-1].x;
        s[i].y=s[i-1].y;
     }

    if (kier==0) {s[0].y+=1; wrr.y-=1; }
    if (kier==1) {s[0].x-=1; wrr.x+=1 ;}
    if (kier==2) {s[0].x+=1; wrr.x-=1 ;}
    if (kier==3) {s[0].y-=1; wrr.y+=1 ;}

    if ((s[0].x==f.x) && (s[0].y==f.y))
     {
        num++; f.x=los(); f.y=los();
        wrr2.x=los(); wrr2.y=los();
     }

    for (int i = 1; i < 81; i++)
    {
    if ((s[0].x==mu[i].x) && (s[0].y==mu[i].y))
     {
        start();
     }
    }

    if (s[0].x>N) s[0].x=0;
    if (s[0].x<0) s[0].x=N;
    if (s[0].y>M) s[0].y=0;
    if (s[0].y<0) s[0].y=M;
    if (wrr.x>N) wrr.x=0;
    if (wrr.x<0) wrr.x=N;
    if (wrr.y>M) wrr.y=0;
    if (wrr.y<0) wrr.y=M;

    for (int i=1;i<num;i++)
    {
     if (s[0].x==s[i+1].x && s[0].y==s[i+1].y)
      num = i;
    }

    for (int i=1;i<num;i++)
    {
     if (s[i].x==wrr.x && s[i].y==wrr.y)
      num = i;
    }

     if (s[0].x==wrr2.x && s[0].y==wrr2.y)
      start();

    if (num > najw)
    {
        najw = num;
}}

int main()
{
    srand(time(0));

    sf::RenderWindow window(sf::VideoMode(w, h+100), "Wonsz rzeczny");

    sf::Texture t1,t2,t3,t4,t5;
    t1.loadFromFile("white.png");
    t2.loadFromFile("red.png");
    t3.loadFromFile("green.png");
    t4.loadFromFile("gray.png");
    t5.loadFromFile("orange.png");

    sf::Sprite sprite1(t1);
    sf::Sprite sprite2(t2);
    sf::Sprite sprite3(t3);
    sf::Sprite sprite4(t4);
    sf::Sprite sprite5(t5);

    sf::Font font;
    if(!font.loadFromFile("foncik.ttf"))
        throw("Could not");

    sf::Text najtext, najwyn, akwyn, aktext;
    najwyn.setFont(font);  akwyn.setFont(font);   najtext.setFont(font);   aktext.setFont(font);
    najwyn.setCharacterSize(50); akwyn.setCharacterSize(50); najtext.setCharacterSize(20); aktext.setCharacterSize(20);
    najwyn.setColor(sf::Color::Green); najtext.setColor(sf::Color::Green);
    najwyn.setStyle(sf::Text::Bold); najtext.setStyle(sf::Text::Bold); akwyn.setStyle(sf::Text::Bold); aktext.setStyle(sf::Text::Bold);
    najwyn.setPosition(w-100,h+40);  najtext.setPosition(w-100,h+20);  akwyn.setPosition(0,h+40);  aktext.setPosition(0,h+20);
    najtext.setString("Najlepszy"); aktext.setString("Aktualny wynik");

    sf::Clock clock;
    float timer=0, delay=0.09;

    start();

    while (window.isOpen())
    {
        float time = clock.getElapsedTime().asSeconds();
        clock.restart();
        timer+=time;

        sf::Event e;
        while (window.pollEvent(e))
        {
            if (e.type == sf::Event::Closed)
                window.close();
        }

        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) if (kier!=2) kier=1;
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) if (kier!=1) kier=2;
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) if (kier!=0) kier=3;
        if ( sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) if (kier!=3) kier=0;


        if (!gra) continue;

        if (timer>delay) {timer=0; Tick();}

   // rysowanie
    window.clear();
    najwyn.setString(std::to_string(najw));
    akwyn.setString(std::to_string(num));
    if (num == najw)
    {
        najwyn.setColor(sf::Color::Yellow); najtext.setColor(sf::Color::Yellow); akwyn.setColor(sf::Color::Yellow); aktext.setColor(sf::Color::Yellow);
    }
    else
    {
        najwyn.setColor(sf::Color::Green); najtext.setColor(sf::Color::Green); akwyn.setColor(sf::Color::White); aktext.setColor(sf::Color::White);
    }

    window.draw(najwyn);
    window.draw(akwyn);
    window.draw(najtext);
    window.draw(aktext);

    for (int i=1; i<81;)
    for (int i1 = 0; i1 < N; i1+=4)
    for (int i2 = 0; i2 < M; i2+=4)
    {
        sprite1.setPosition(i1*roz, i2*roz);
        window.draw(sprite1);
        mu[i].x = i1;
        mu[i].y = i2;
        i++;
    }

    for (int i=0;i<num;i++)
        {
            sprite2.setPosition(s[i].x*roz, s[i].y*roz);
            window.draw(sprite2);
        }

    sprite3.setPosition(f.x*roz, f.y*roz);
    window.draw(sprite3);

    sprite4.setPosition(wrr.x*roz, wrr.y*roz);
    window.draw(sprite4);

    sprite5.setPosition(wrr2.x*roz, wrr2.y*roz);
    window.draw(sprite5);

    window.display();
    }
    return 0;
}
