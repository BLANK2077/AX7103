`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Module Name:    lcd_disp
//
//////////////////////////////////////////////////////////////////////////////////
module lcd_disp(
		  input           lcd_clk_i,
	      input           lcd_rst, 	
	      input           key2,    
	      input [255:0]   ddr_data,        //DDR�е�ͼ������  
	      
          output          lcd_clk,
          output          lcd_en,
		  output          lcd_hsync,
		  output          lcd_vsync,
		  output [7:0]    lcd_r,
		  output [7:0]    lcd_g,
		  output [7:0]    lcd_b,

	      output reg     ddr_rden,         //ddr�������ź�
		  input           ddr_init_done

    );
    
    //-----------------------------------------------------------//
    // ˮƽɨ��������趨480*272 60Hz LCD
    //-----------------------------------------------------------//
    parameter LinePeriod =525;           //��������
    parameter H_SyncPulse=41;            //��ͬ�����壨Sync a��
    parameter H_BackPorch=2;             //��ʾ���أ�Back porch b��
    parameter H_ActivePix=480;           //��ʾʱ��Σ�Display interval c��
    parameter H_FrontPorch=2;            //��ʾǰ�أ�Front porch d��
    parameter Hde_start=43;
    parameter Hde_end=523;
    
    //-----------------------------------------------------------//
    // ��ֱɨ��������趨480*272 60Hz LCD
    //-----------------------------------------------------------//
    parameter FramePeriod =286;           //��������
    parameter V_SyncPulse=10;             //��ͬ�����壨Sync o��
    parameter V_BackPorch=2;              //��ʾ���أ�Back porch p��
    parameter V_ActivePix=272;            //��ʾʱ��Σ�Display interval q��
    parameter V_FrontPorch=2;             //��ʾǰ�أ�Front porch r��
    parameter Vde_start=12;
    parameter Vde_end=284;


  reg[10 : 0] x_cnt;
  reg[9 : 0]  y_cnt;
  reg[4 : 0] lcd_r_reg;
  reg[5 : 0] lcd_g_reg;
  reg[4 : 0] lcd_b_reg;  

  
  reg hsync_r;
  reg vsync_r; 
  reg vsync_de;
  reg hsync_de;
 
  reg [255:0] ddr_data_reg;               //ddr���������ݴ洢
  reg  [3:0] num_counter;       
		  
  reg first_read;
  
  reg [15:0] key2_counter;                 //�������Ĵ���
  reg lcd_dis_mode; 
  
//----------------------------------------------------------------
////////// ˮƽɨ�����
//----------------------------------------------------------------
always @ (posedge lcd_clk_i)
       if(lcd_rst)    x_cnt <= 1;
       else if(x_cnt == LinePeriod) x_cnt <= 1;
       else x_cnt <= x_cnt+ 1;
		 
//----------------------------------------------------------------
////////// ˮƽɨ���ź�hsync,hsync_de����
//----------------------------------------------------------------
always @ (posedge lcd_clk_i)
   begin
       if(lcd_rst) hsync_r <= 1'b1;
       else if(x_cnt == 1) hsync_r <= 1'b0;             //����hsync�ź�
       else if(x_cnt == H_SyncPulse) hsync_r <= 1'b1;
		 
		 		 
	    if(1'b0) hsync_de <= 1'b0;
       else if(x_cnt == Hde_start) hsync_de <= 1'b1;    //����hsync_de�ź�
       else if(x_cnt == Hde_end) hsync_de <= 1'b0;					 
 
	end

//----------------------------------------------------------------
////////// ��ֱɨ�����
//----------------------------------------------------------------
always @ (posedge lcd_clk_i)
       if(lcd_rst) y_cnt <= 1;
       else if(y_cnt == FramePeriod) y_cnt <= 1;
       else if(x_cnt == LinePeriod) y_cnt <= y_cnt+1;

//----------------------------------------------------------------
////////// ��ֱɨ���ź�vsync, vsync_de����
//----------------------------------------------------------------
always @ (posedge lcd_clk_i)
  begin
       if(1'b0) vsync_r <= 1'b1;
       else if(y_cnt == 1) vsync_r <= 1'b0;    //����vsync�ź�
       else if(y_cnt == V_SyncPulse) vsync_r <= 1'b1;
		 
	    if(1'b0) vsync_de <= 1'b0;
       else if(y_cnt == Vde_start) vsync_de <= 1'b1;    //����vsync_de�ź�
       else if(y_cnt == Vde_end) vsync_de <= 1'b0;	 
  end
		 

//----------------------------------------------------------------
////////// һ֡ͼ��֮ǰ��ǰ����һ��ddr������
//---------------------------------------------------------------- 
always @(posedge lcd_clk_i)
begin
   if (lcd_rst) begin
	    first_read<=1'b0;
     end
   else begin
       if ((x_cnt==Hde_start-1'b1) && (y_cnt==Vde_start-1'b1))      //��ǰ����һ��LCD��ʾ����
	         first_read<=1'b1;
		 else
		     first_read<=1'b0;		   
	   end
end
//----------------------------------------------------------------
////////// ddr�������źŲ�������	,256bit��DDR����ת��16���������
//---------------------------------------------------------------- 
 always @(negedge lcd_clk_i)
 begin
   if (lcd_rst) begin
		 ddr_data_reg<=256'd0;
		 lcd_r_reg<=5'd0;
		 lcd_g_reg<=6'd0;
		 lcd_b_reg<=5'd0;
		 num_counter<=4'd0;
		 ddr_rden<=1'b0;   
   end
   else begin
	  if (first_read==1'b1) 
			  ddr_rden<=1'b1;  	
     else if (hsync_de && vsync_de ) begin             //���LCD�����Ч��ͼ������
        num_counter <= num_counter + 1;
          case(num_counter)
            4'b0000:begin 
              lcd_b_reg<=ddr_data_reg[255:251];           //��N������
              lcd_g_reg<=ddr_data_reg[250:245];
              lcd_r_reg<=ddr_data_reg[244:240];     
              ddr_rden<=1'b1;                               //ddr����������
              end
            4'b0001:begin                                  //��N+1������
              lcd_b_reg<=ddr_data_reg[239:235];
              lcd_g_reg<=ddr_data_reg[234:229];
              lcd_r_reg<=ddr_data_reg[228:224];         
              ddr_rden<=1'b0; 
              end                        
            4'b0010:begin                                 //��N+2������
              lcd_b_reg<=ddr_data_reg[223:219];
              lcd_g_reg<=ddr_data_reg[218:213];
              lcd_r_reg<=ddr_data_reg[212:208];
              ddr_rden<=1'b0;
              end
            4'b0011:begin                                //��N+3������
              lcd_b_reg<=ddr_data_reg[207:203];
              lcd_g_reg<=ddr_data_reg[202:197];
              lcd_r_reg<=ddr_data_reg[196:192];         
              ddr_rden<=1'b0;    
              end                        
            4'b0100:begin                                //��N+4������
              lcd_b_reg<=ddr_data_reg[191:187];
              lcd_g_reg<=ddr_data_reg[186:181];
              lcd_r_reg<=ddr_data_reg[180:176];
              ddr_rden<=1'b0;
              end        
            4'b0101:begin                                //��N+5������
              lcd_b_reg<=ddr_data_reg[175:171];
              lcd_g_reg<=ddr_data_reg[170:165];
              lcd_r_reg<=ddr_data_reg[164:160]; 
              ddr_rden<=1'b0;
              end    
            4'b0110:begin                                //��N+6������
              lcd_b_reg<=ddr_data_reg[159:155];
              lcd_g_reg<=ddr_data_reg[154:149];
              lcd_r_reg<=ddr_data_reg[148:144];  
              ddr_rden<=1'b0;
              end    
            4'b0111:begin                                  //��N+7������
              lcd_b_reg<=ddr_data_reg[143:139];          
              lcd_g_reg<=ddr_data_reg[138:133];
              lcd_r_reg<=ddr_data_reg[132:128];           
              ddr_rden<=1'b0;
              end 
            4'b1000:begin 
              lcd_b_reg<=ddr_data_reg[127:123];           //��N��+8����
              lcd_g_reg<=ddr_data_reg[122:117];
              lcd_r_reg<=ddr_data_reg[116:112];  
              end
            4'b1001:begin                                  //��N+9������
              lcd_b_reg<=ddr_data_reg[111:107];
              lcd_g_reg<=ddr_data_reg[106:101];
              lcd_r_reg<=ddr_data_reg[100:96];  
              ddr_rden<=1'b0; 
              end                        
            4'b1010:begin                                 //��N+10������
              lcd_b_reg<=ddr_data_reg[95:91];
              lcd_g_reg<=ddr_data_reg[90:85];
              lcd_r_reg<=ddr_data_reg[84:80];    
              ddr_rden<=1'b0;
              end
            4'b1011:begin                                //��N+11������
              lcd_b_reg<=ddr_data_reg[79:75];
              lcd_g_reg<=ddr_data_reg[74:69];
              lcd_r_reg<=ddr_data_reg[68:64];   
              ddr_rden<=1'b0;    
              end                        
            4'b1100:begin                                //��N+12������
              lcd_b_reg<=ddr_data_reg[63:59];
              lcd_g_reg<=ddr_data_reg[58:53];
              lcd_r_reg<=ddr_data_reg[52:48]; 
              ddr_rden<=1'b0;
              end        
            4'b1101:begin                                //��N+13������
              lcd_b_reg<=ddr_data_reg[47:43];
              lcd_g_reg<=ddr_data_reg[42:37];
              lcd_r_reg<=ddr_data_reg[36:32];  
              ddr_rden<=1'b0;
              end    
            4'b1110:begin                                //��N+14������
              lcd_b_reg<=ddr_data_reg[31:27];
              lcd_g_reg<=ddr_data_reg[26:21];
              lcd_r_reg<=ddr_data_reg[20:16];   
              ddr_rden<=1'b0;
              end    
            4'b1111:begin                                //��N+15������
              lcd_b_reg<=ddr_data_reg[15:11];          
              lcd_g_reg<=ddr_data_reg[10:5];
              lcd_r_reg<=ddr_data_reg[4:0];    
              ddr_data_reg<=ddr_data;                   //ddr���ݸı�                     
              ddr_rden<=1'b0;
              end                    
                               
      default:begin
           lcd_r_reg<=5'd0;                    
           lcd_g_reg<=6'd0;
           lcd_b_reg<=5'd0;
           //num_counter<=4'b0000;    
           ddr_rden<=1'b0;
           end
      endcase;
     end		 
	  else begin
			lcd_r_reg<=5'd0;                    
            lcd_g_reg<=6'd0;
            lcd_b_reg<=5'd0;
			num_counter<=4'd0;	
			ddr_rden<=1'b0;
			ddr_data_reg<=ddr_data;                     //ddr���ݸı�
	  end
	end
end

 //��ť�������	
  always @(posedge lcd_clk)
	  begin
	    if (key2==1'b0)                               //�����ťû�а��£��Ĵ���Ϊ0
	       key2_counter<=0;
	    else if ((key2==1'b1)& (key2_counter<=16'hc350))      //�����ť���²�����ʱ������1ms,����      
          key2_counter<=key2_counter+1'b1;
  	  
       if (key2_counter==16'hc349)                //һ�ΰ�ť��Ч���ı���ʾģʽ
		    begin
		      if(lcd_dis_mode==1'b1)
			      lcd_dis_mode<=1'b0;
			   else
			      lcd_dis_mode<=lcd_dis_mode+1'b1; 
          end	
     end	


  assign lcd_clk = lcd_clk_i;
  assign lcd_en = hsync_de & vsync_de;
  assign lcd_hsync = hsync_r;
  assign lcd_vsync = vsync_r;  
  assign lcd_r = lcd_dis_mode ? {lcd_r_reg[4:0],lcd_r_reg[2:0]} : x_cnt[7:0];
  assign lcd_g = lcd_dis_mode ? {lcd_g_reg[5:0],lcd_g_reg[1:0]} : x_cnt[7:0];
  assign lcd_b = lcd_dis_mode ? {lcd_b_reg[4:0],lcd_b_reg[2:0]} : x_cnt[7:0];
 

endmodule
