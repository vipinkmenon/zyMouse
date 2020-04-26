`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Company: 
// Engineer: 
// 
// Create Date: 04/18/2020 01:34:20 PM
// Design Name: 
// Module Name: pulseGen
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
`define clockFreq 100000000 //In Hertz
`define minPulseWidth 0.01

module pulseGen(
    input        i_clk,
    input        i_button,
    input [31:0] i_counter_max_Value,
    output reg   o_pulse
    );
    
integer counter=0;
localparam clockCount = `minPulseWidth*`clockFreq;
    
always @(posedge i_clk)
begin
    if((counter < i_counter_max_Value)&i_button)
        counter <= counter+1;
    else
        counter <= 0;
end
    
always @(posedge i_clk)
begin
    if(counter == i_counter_max_Value)
        o_pulse <= 1'b1;
    else
        o_pulse <= 1'b0;
end
    
endmodule
