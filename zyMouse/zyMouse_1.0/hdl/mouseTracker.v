`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/18/2020 01:09:34 PM
// Design Name: 
// Module Name: mouseTracker
// Project Name: 
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////
`define clockSpeed 100000000

module mouseTracker(
input             i_clk,
input             i_reset,
input      [31:0] i_counter_max_Value,
input             i_button_left,
input             i_button_right,
input             i_button_up,
input             i_button_down,
output reg [15:0] o_x_pos,
output reg [15:0] o_y_pos,
input      [15:0] i_max_x,
input      [15:0] i_max_y,
output reg        o_intr
);
    
    
wire incrementX;
wire incrementY;    
wire decrementX;    
wire decrementY;    

wire button_Left;
wire button_Right;
wire button_up;
wire button_down;
    
always @(posedge i_clk)
begin
    if(i_reset)
    begin
        o_x_pos <= i_max_x/2;
        o_y_pos <= i_max_y/2;
        o_intr  <= 1'b0;  
    end
    else
    begin
        o_intr  <= 1'b0; 
        if(incrementX)
        begin
            if(o_x_pos < i_max_x)
            begin
                o_x_pos <= o_x_pos + 1;
                o_intr  <= 1'b1;
            end 
        end
        else if(decrementX)
        begin
            if(o_x_pos > 0)
            begin
                o_x_pos <= o_x_pos - 1;
                o_intr  <= 1'b1;
            end        
        end
        
        if(incrementY)
        begin
            if(o_y_pos < i_max_y)
            begin
                o_y_pos <= o_y_pos + 1;
                o_intr  <= 1'b1;
            end
        end
        else if(decrementY)
        begin
            if(o_y_pos > 0)
            begin
                o_y_pos <= o_y_pos - 1;
                o_intr  <= 1'b1;
            end        
        end   
    end
end




debounce dbLeft(
    .i_clk(i_clk),
    .i_button(i_button_left),
    .o_press(button_Left)
);

debounce dbRight(
    .i_clk(i_clk),
    .i_button(i_button_right),
    .o_press(button_Right)
);

debounce dbUp(
    .i_clk(i_clk),
    .i_button(i_button_up),
    .o_press(button_up)
);

debounce dbDown(
    .i_clk(i_clk),
    .i_button(i_button_down),
    .o_press(button_down)
);

pulseGen pGLeft(
  .i_clk(i_clk),
  .i_button(button_Left),
  .i_counter_max_Value(i_counter_max_Value),
  .o_pulse(decrementX)
);

pulseGen pGRight(
  .i_clk(i_clk),
  .i_button(button_Right),
  .i_counter_max_Value(i_counter_max_Value),
  .o_pulse(incrementX)
);

pulseGen pGUp(
  .i_clk(i_clk),
  .i_button(button_up),
  .i_counter_max_Value(i_counter_max_Value),
  .o_pulse(decrementY)
);

pulseGen pGDown(
  .i_clk(i_clk),
  .i_button(button_down),
  .i_counter_max_Value(i_counter_max_Value),
  .o_pulse(incrementY)
);
    
endmodule
