/*   WIN-TC BGI ͼ�α��ģ�� */

#include "Conio.h"
#include "graphics.h"

#define closegr closegraph

void initgr(void) /* BGI��ʼ�� */
{
  int gd = DETECT, gm = 0; /* ��gd = VGA,gm = VGAHI��ͬ��Ч�� */
  registerbgidriver(EGAVGA_driver);/* ע��BGI��������Բ���Ҫ.BGI�ļ���֧������ */
  initgraph(&gd, &gm, "");

}

int main(void)
{
    int left,top,right,butt;
  initgr(); /* BGI��ʼ�� */

  /*****�˲���������Լ��Ĵ��룬����
  line(25, 25, 220, 220);
  circle(100, 100, 50);
  �ȵ�*****/
  left=30;
    top=40;
    right=50;
    butt=60;

    rectangle(left,top,right,butt);

  getch(); /* ��ͣһ�£�����ǰ���ͼ��������н�� */
  closegr(); /* �ָ�TEXT��Ļģʽ */
  return 0;
}
