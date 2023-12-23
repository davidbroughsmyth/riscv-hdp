module alu_tb;
    reg [3:0] a, b;
    reg [2:0] operation;
    wire [3:0] result;
    wire zero;

    alu dut(a, b, operation, result, zero);

    // Test stimuli here
    initial begin
        // Example test case
        a = 4'b0101;
        b = 4'b0011;
        operation = 3'b000; // Addition
        #10;

        // Add more test cases as needed
    end

endmodule

