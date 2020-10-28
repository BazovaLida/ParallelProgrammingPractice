--Basics Of Parallel Programming
--Laboratory work 1
--"Flows in ADA language. Tasks"
--Variant 1
--F1: d = (A * ((B + C) * (MA * ME)))
--F2: MG = SORT(MF) * MK + ML
--F3: O = SORT(R + S) * (MT * MP)
--Bazova L.
--IV-81
--Date: 10.09.2020
--data.ads file
----------------------------------------
generic
   n: Integer;
package data is
   ---Declaration of private types Vector and Matrix
   type Vector is private;
   type Matrix is private;
   
   --Setting Vector/Matrix from console
   procedure Enter_vec(A: out Vector);
   procedure Enter_Matr(MA: out Matrix);
   
   --Filling Vector/Matrix by constant numbers
   procedure fill_vec(c: in Integer; A: out Vector); --c - constant
   procedure fill_Matr(c: in Integer; MA: out Matrix);--c - constant
   
   --Changing one value in Vector/Matrix
   procedure change_matr_value(MA: out Matrix; i, j, c: in Integer);
   --c - constant, i j - place
   procedure change_vec_value(A: out Vector; i, c: in integer);
   --c - constant, i - place
   
   --Write Vector/Matrix in console
   procedure put_vec(A: in Vector; name: in String);
   procedure put_matr(MA: in Matrix; name: in String);
   
   --Math operations with Vector/Matrix
   function sum_vec(A, B: in Vector) return Vector;
   function scalar_multiply_vec(A, B: in Vector) return Integer;
   procedure sort_vec(A: in out Vector);
   function sum_matr(MA, ME: in Matrix) return Matrix;
   function multiply_matr(MA, ME: in Matrix) return Matrix;
   procedure sort_matr(MA: in out Matrix);   
   function multiply_vec_matr
     (V: in Vector; MA: in Matrix) return Vector;
   
   --Calculations of functions
   procedure Func1(A, B, C: in Vector; MA, ME: in Matrix; d: out Integer);
   procedure Func2(MF, MK, ML: in Matrix; MG: out Matrix);
   procedure Func3(R, S: in Vector; MT, MP: in Matrix; O: out Vector);
   
   --Declaration of private types in private part 
private
   type Vector is array (1..n) of Integer;
   type Matrix is array (1..n) of Vector;
end data;
