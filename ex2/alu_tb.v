`default_nettype none
`timescale 1ns/1ns

module alu_tb;
    reg [3:0] a, b;
    reg [2:0] operation;
    wire [3:0] result;
    wire zero;

    alu dut(a, b, operation, result, zero);

    // Test stimuli here
    initial begin
        $display("4bit ALU tests");
        $dumpfile ("alu.vcd");
        $dumpvars (0, alu_tb);
        // Example test case
        a = 4'b0101;
        b = 4'b0011;
        operation = 3'b000; // Addition
        #10;

        a = 4'b0101;
        b = 4'b0011;
        operation = 3'b001; // Subtract
        #10;

        a = 4'b0101;
        b = 4'b0011;
        operation = 3'b010; // And
        #10;
	
        a = 4'b0101;
        b = 4'b0011;
        operation = 3'b011; // OR
        #10;

        a = 4'b0101;
        b = 4'b0011;
        operation = 3'b100; // XOR
        #10;
    end
    
    initial
        $monitor("A:%0d  Op:%0d B:%0d Result:%0d",a,operation,b,result);
endmodule

