main:
  addi x29, x0, -1
  addi x30, x0, 37
  add x31, x30, x29
  li x3, 10
  li x4, 10
  bne x3, x4, fail
  beq x0, x0, success
fail:
  beq x0, x0, fail
success:
  
