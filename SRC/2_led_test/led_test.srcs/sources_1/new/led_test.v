//===========================================================================
// Module name: led_test.v
// ����: ÿ��0.25�����ε����������ϵ�LED0~LED4
//===========================================================================
`timescale 1ns / 1ps

module led_test (
                  sys_clk_p,      // �������ϲ������ʱ��200Mhz�� ����
                  sys_clk_n,      // �������ϲ������ʱ��200Mhz�� ����  
                  rst_n,          // ���İ������븴λ����
                  led             // ���LED��,���ڿ��ƿ��������ĸ�LED(LED1~LED4)
             );
             
//===========================================================================
// PORT declarations
//===========================================================================
input sys_clk_p;
input sys_clk_n;
input rst_n;
output [3:0] led;

//�Ĵ�������
reg [31:0] timer;                  
reg [3:0] led;

//===========================================================================
// ���ʱ��ת���ɵ���ʱ��
//===========================================================================
wire sys_clk_ibufg;
 IBUFGDS #
       (
        .DIFF_TERM    ("FALSE"),
        .IBUF_LOW_PWR ("FALSE")
        )
       u_ibufg_sys_clk
         (
          .I  (sys_clk_p),            //���ʱ�ӵ��������룬��Ҫ�Ͷ���ģ��Ķ˿�ֱ������
          .IB (sys_clk_n),           // ���ʱ�ӵĸ������룬��Ҫ�Ͷ���ģ��Ķ˿�ֱ������
          .O  (sys_clk_ibufg)        //ʱ�ӻ������
          );
          
//===========================================================================
// ����������:ѭ������0~1��
//===========================================================================
  always @(posedge sys_clk_ibufg or negedge rst_n)    //���ʱ�ӵ������غ͸�λ���½���
    begin
      if (~rst_n)                           //��λ�źŵ���Ч
          timer <= 0;                       //����������
      else if (timer == 32'd199_999_999)    //������ʹ�õľ���Ϊ200MHz��1�����(200M*1-1=199_999_999)
          timer <= 0;                       //�������Ƶ�4�룬����������
      else
		    timer <= timer + 1'b1;            //��������1
    end

//===========================================================================
// LED�ƿ���
//===========================================================================
  always @(posedge sys_clk_ibufg or negedge rst_n)   //���ʱ�ӵ������غ͸�λ���½���
    begin
      if (~rst_n)                          //��λ�źŵ���Ч
          led <= 4'b0000;                  //LED�����ȫΪ�ͣ��ĸ�LED����           
      else if (timer == 32'd49_999_999)    //�������Ƶ�0.25�룬
          led <= 4'b0001;                  //LED1Ϩ��
      else if (timer == 32'd99_999_999)    //�������Ƶ�0.5�룬
          led <= 4'b0010;                  //LED2Ϩ��
      else if (timer == 32'd149_999_999)   //�������Ƶ�0.75�룬
          led <= 4'b0100;                  //LED3Ϩ��                           
      else if (timer == 32'd199_999_999)   //�������Ƶ�1�룬
          led <= 4'b1000;                  //LED4Ϩ��       
    end
    
endmodule