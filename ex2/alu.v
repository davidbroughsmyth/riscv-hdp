`default_nettype none
`timescale 1ns/1ns
module alu(
    input [3:0] a, b,
    input [2:0] operation,
    output reg [3:0] result,
    output reg zero
);

always @(*) begin
    case (operation)
        3'b000: result = a + b;
        3'b001: result = a - b;
        3'b010: result = a & b;
        3'b011: result = a | b;
        3'b100: result = a ^ b;
        default: result = 4'b0000;
    endcase

    zero = (result == 4'b0000);
end

endmodule
