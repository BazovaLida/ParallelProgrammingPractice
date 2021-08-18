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
--data.adb file
----------------------------------------
with Ada.Text_IO, Ada.Integer_Text_IO;
use Ada.Text_IO, Ada.Integer_Text_IO;

package body data is
   --Read Vector from console
   procedure Enter_vec(A: out Vector) is
   begin
      for i in 1..n loop
         get(A(i));
      end loop;
   end Enter_vec;

   --Read Matrix from console
   procedure Enter_Matr(MA: out Matrix) is
   begin
      for i in 1..n loop
         for j in 1..n loop
            Get(MA(i)(j));
         end loop;
      end loop;
   end Enter_Matr;
   
   --Filling Vector by constant numbers
   procedure fill_vec(c: in Integer; A: out Vector) is
   begin
      for i in 1..n loop
         A(i) := c;
      end loop;
   end fill_vec;
      
   --Filling Matrix by constant numbers
   procedure fill_Matr(c: in Integer; MA: out Matrix) is
   begin
      for i in 1..n loop
         for j in 1..n loop
            MA(i)(j) := c;
         end loop;
      end loop;
   end fill_Matr;
   
   --Changing one value in Vector
   procedure change_vec_value(A: out Vector; i, c: integer) is
      --c - constant, i - place
   begin
      A(i) := c;
   end change_vec_value;
      
   --Changing one value in Matrix
   procedure change_matr_value(MA: out Matrix; i, j, c: Integer) is
      --c - constant, i j - place
   begin
      MA(i)(j) := c;
   end change_matr_value;
      
   --Write Vector in console
   procedure put_vec(A: in Vector; name: in String) is
   begin
      Put("Vector " & name & " = (");
      for i in 1..n loop
         put(A(i), 6);
      end loop;
      Put_Line(")");
   end put_vec;

   --Write Matrix in console
   procedure put_matr(MA: in Matrix; name: in String) is
   begin
      Put_Line("Matrix " & name);
      for i in 1..n loop
         for j in 1..n loop
            Put(MA(i)(j));
            Put(" ");
         end loop;
         Put_Line(" ");
      end loop;
   end put_matr;

   function sum_vec(A, B: in Vector) return Vector is
      V: Vector;
   begin
      for i in 1..n loop
         V(i) := A(i) + B(i);
      end loop;
      return V;
   end sum_vec;
   
   function scalar_multiply_vec(A, B: in Vector) return Integer is
      t: Integer; --temporary value
   begin
      t := 0;
      for i in 1..n loop
         t := t + A(i) * B(i);
      end loop;
      return t;
   end scalar_multiply_vec;
   
   procedure sort_vec(A: in out Vector) is
      t: Integer; --temporary value
   begin
      for i in 1..n loop
         for j in i..n loop
            if A(i) > A(j) then
               t := A(j);
               A(j) := A(i);
               A(i) := t;
            end if;
         end loop;
      end loop;
   end sort_vec;
      
   function sum_matr(MA, ME: in Matrix) return Matrix is
      MT: Matrix; --temporary matrix
   begin
      for i in 1..n loop
         for j in 1..n loop
            MT(i)(j) := MA(i)(j) + ME(i)(j);
         end loop;
      end loop;
      return MT;
   end sum_matr;
   
   function multiply_matr(MA, ME: in Matrix) return Matrix is
      MT: Matrix; --temporary matrix
      t: Integer; --temporary value
   begin
      for k in 1..n loop
         for i in 1..n loop
            t := 0;
            for j in 1..n loop
               t := t + MA(k)(j)*ME(j)(i);
               MT(k)(i) := t;
            end loop;
         end loop;
      end loop;
      return MT;
   end multiply_matr;
   
   procedure sort_matr(MA: in out Matrix) is
      MT: Matrix; --temporary matrix
      t: Integer; --temporary value
   begin
      for i in 1..n loop
         for j in 1..n loop
            MT(i)(j) := MA(i)(j);
         end loop;
      end loop;
      for k in 1..n loop
         for i in reverse 1..n loop
            for j in 1..(i-1) loop
               if MT(k)(j) < MT(k)(j+1) then
                  t := MT(k)(j);
                  MT(k)(j) := MT(k)(j+1);
                  MT(k)(j+1) := t;
               end if;
            end loop;
         end loop;
      end loop;
      MA := MT;
   end sort_matr;
         
   function multiply_vec_matr
     (V: in Vector; MA: in Matrix) return Vector is
      m: Integer; --temporary max
      T: Vector;  --tomporary vector
   begin
      for i in 1..n loop
         m := 0;
         for j in 1..n loop
            m := m + V(i) * MA(j)(i);
         end loop;
         T(i) := m;
      end loop;
      return T;
   end multiply_vec_matr;
   
   procedure Func1(A, B, C: in Vector; MA, ME: in Matrix; d: out Integer) is
      T: Vector; --temporary vector
      MT: Matrix;--temporary matrix
   begin
      T := sum_vec(B, C);
      MT := multiply_matr(MA, ME);
      T := multiply_vec_matr(T, MT);
      d := scalar_multiply_vec(A, T);
      --Displaying result
      Put_Line(Integer'Image(d));
   end Func1;
   
   procedure Func2(MF, MK, ML: in Matrix; MG: out Matrix) is
      MT: Matrix;--temporary matrix
   begin
      MT := MF;
      sort_matr(MT);
      MT := multiply_matr(MT, MK);
      MG := sum_matr(MT, ML);
      --Displaying result
      put_matr(MG, "MG");
   end Func2;
   
   --Calculation F3: O = SORT(R + S) * (MT * MP)
   procedure Func3(R, S: in Vector; MT, MP: in Matrix; O: out Vector) is
      T: Vector; --temporary vector
      MQ: Matrix;--temporary matrix
   begin
      T := sum_vec(R, S);
      sort_vec(T);
      MQ := multiply_matr(MT, MP);
      O := multiply_vec_matr(T, MQ);
      --Displaying result
      put_vec(O, "O");
   end Func3;
end data;
