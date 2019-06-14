# Project1 Vector / Matrix Calculator

## Vector
- Dot of Vector(1%)
- Vector addition(1%)
- Scalar Multiplication with vector (1%)
- Norm of Vector (2%)
- Vector normalization (2%)
- Cross product (2%)
- Component of a on b (2%)
- Projection of a on b (2%)
- Triangle area (2%)
- Parallel judgement(2%)
- Orthogonal judgement(5%)
- The angle between two vectors(degree) (3%)
- The plane normal that is produced by two vectors (5%)
- Linear independent judgement(10%)
- Use Gram-schmidt to find orthonormal basis(10%)

## Matrix
- Matrix addition & subtraction(2%)
- Matrix Multiplication(2%)
- Rank of Matrix(5%)
- Matrix Transpose(2%)
- Solve Linear System(5%)
- Determinants of Matrix(3%)
- Inverse Matrix(6%)
- Adjoint of Matrix(3%)
- Eigen Vector and Eigen Value(10%)
- Power Method of Eigen value(6%)
- Method of Least Square(6%)                             

## Interface
![image](https://user-images.githubusercontent.com/4931242/59510096-6aaeb400-8ee5-11e9-9d7f-7aff9cda58fd.png)

## Load File Rule
- Only support text File

## Vector File Format
`Vector Example.txt`
```
3           // Vector amount in File
V           // Data type
3           // Vector Dimension
1 5 6       // Vector Value
V
3
2 4 10
V
3
5 4 -1
```

`Matrix Example.txt`
```
3                   // Matrix amount in File
M                   // Data Type
2 2                 // Matrix Dimension (row, column)
-11   -46           // row 1 value
-8   -99            // row 2 value
M
3 1
27
-3
-56
M
3 3
-30    47    47
75   -19     6
77     7   -18
```

## Useful function
- Can Click MenuStrip to show function command in input textbox
- Can Double-Click Vector/Matrix Item to show item text in input textbox 

## Input Command Format
- Can use menustrip to find function command
- e.g. `printM $m1`, `funcV isParallel($v1, $v0)`, `calV $v0+$v1`

## Test Demo
![image](https://user-images.githubusercontent.com/4931242/59511096-fd505280-8ee7-11e9-940b-f349f80a678c.png)