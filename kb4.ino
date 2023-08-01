#include <Keyboard.h>
// #include <Mouse.h>

#ifndef _countof
#define _countof(array) (sizeof(array)/sizeof(array[0]))
#endif

// 延时计数器：根据loop的时钟循环级别修改:
// 如loop每毫秒循环5次，这个值设置为50，则约为调用了delay(10),
// 但和delay堵塞模式不同，这个计算器模式不会堵塞
#define KEY_DELAYCNT   50

// key对应的引脚id:
const int pinw=2;
const int pine=3;
const int pind=4;
const int pinc=5;
const int pinx=6;
const int pinz=7;
const int pina=8;
const int pinq=9;

// 光电按键 "未加电" 和 "加电后按下" 状态相同，即digitalRead均为HIGH，需判断是否加过电，
// 否则未加电时如同键盘长按，一直发送键值。
// enabled变量，用于控制是否加电生效：
int enabled = 0;
// 只有加电后才进入正常流程:
// 加电，未按钮按键时，检测到的应为LOW，只有全键均检测到LOW，才激活，进入加电状态
void isenabled()
{
  for(int keyid=pinw; keyid<=pinq; keyid++)
  {
    if ( digitalRead(keyid) != LOW )
    {
      enabled = 0;
      return;
    }
  }
  // 全部为LOW，激活
  enabled = 1;
  return;
}

// 用一个状态数组来保存每一个键的发送状态:
// 小余0时表示空闲;
// 发送键时设置为KEY_DELAYCNT，每次检测减一，直到为0时发出键值，设置为空闲;
// 周期内重复按键只发一次。
int arsta[8] = {-1,-1,-1,-1,-1,-1,-1,-1};

// 初始化
void setup() 
{
  for(int keyid = pinw; keyid <= pinq; keyid++)
  {
    pinMode(keyid, INPUT_PULLUP);
  }
  // 初始化为-1
  memset(arsta, -1, sizeof(arsta));
  return;
}

// 检查是否有键需要发出
void checkkeys()
{
  // 如果非enabled状态，则置位所有待发键值，无需发送了
  if (!enabled)
  {
    memset(arsta, -1, sizeof(arsta));
    return;
  }
  
  for ( int i=0; i < _countof(arsta); i++)
  {
    // 空闲，忽略
    if (arsta[i] < 0)
      continue;

    // 非空闲时, 计算器递减, 如等于0了，发出去, 并设置为空闲
    if ( --arsta[i]<=0 )
    {
      switch(i+2) // i+2: index 需转为 keyid
      {
        case pinw: 
          Keyboard.write('W'); break;
        case pine: 
          Keyboard.write('E'); break;
        case pind: 
          Keyboard.write('D'); break;
        case pinc: 
          Keyboard.write('C'); break;
        case pinx: 
          Keyboard.write('X'); break;
        case pinz: 
          Keyboard.write('Z'); break;
        case pina: 
          Keyboard.write('A'); break;
        case pinq: 
          Keyboard.write('Q'); break;
      }
      arsta[i] = -1;
    }// end of if
  }// end of for
}

// 设置发送某键
void setkey(int keyid)
{
    // 只有该键空闲时才设置计算器
    if (arsta[keyid-2] < 0)
      arsta[keyid-2] = KEY_DELAYCNT;
    return;  
}

// 直接发
void sendkey(int keyid)
{
  switch(keyid) 
  {
    case pinw: 
      Keyboard.write('W'); break;
    case pine: 
      Keyboard.write('E'); break;
    case pind: 
      Keyboard.write('D'); break;
    case pinc: 
      Keyboard.write('C'); break;
    case pinx: 
      Keyboard.write('X'); break;
    case pinz: 
      Keyboard.write('Z'); break;
    case pina: 
      Keyboard.write('A'); break;
    case pinq: 
      Keyboard.write('Q'); break;
  }
  delay(1);
}

void loop() 
{
   // 检测是否加电激活
  if (!enabled)
  {
    isenabled();
    return;
  }

  // 检测是否有按键需要发出
  //
  // checkkeys();
  // 

  // 如果全部为HIGH，则不会认为是所有按键都被按下，而是"光眼键盘"断电了.
  int powerdown = 1;
  for(int keyid=pinw; keyid<=pinq; keyid++)
  {
    // 按键按下时，如已有待发送同key，则忽略;
    // 否则，只是给数组发出延时计数，由checkkeys()真正延时发出
    if (digitalRead(keyid) == HIGH)
    {
      //
      // setkey(keyid);
      //
      sendkey(keyid);
    }
    else
      powerdown = 0;
  }
  // 重新设置为非激活态
  if (powerdown == 1)
     enabled = 0;

  /* 
  if (digitalRead(pinw) == HIGH)
  {
    setKey(pinw);
  }
  
  if (digitalRead(pine) == HIGH)
  {
    setKey(pine);
  }

  if (digitalRead(pind) == HIGH)
  {
    setKey(pind);
  }

  if (digitalRead(pinc) == HIGH)
  {
    setKey(pinc);
  }

  if (digitalRead(pinx) == HIGH)
  {
    setKey(pinx);
  }

  if (digitalRead(pinz) == HIGH)
  {
    setKey(pinz);
  }

  if (digitalRead(pina) == HIGH)
  {
    setKey(pina);
  }

  if (digitalRead(pinq) == HIGH)
  {
    setKey(pinq);
  }
  */
  return;
}
