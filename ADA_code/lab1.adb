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
--Lab1.adb file
----------------------------------------
with Ada.Text_IO, Ada.Integer_Text_IO, System.Multiprocessors, data;
use Ada.Text_IO, Ada.Integer_Text_IO, System.Multiprocessors;
procedure Lab1 is
   n: Integer := 10;
   package data_pack is new data (n);
   use data_pack;

--Task T1
   task T1 is
      pragma Priority(3);
      pragma Storage_Size(10000); --stack size
      pragma CPU(3);
   end T1;

   task body T1 is
      A, B, C: Vector;
      MA, ME: Matrix;
      d: Integer;
   begin
      Put_Line("task T1 is started");
      --Enter A, B, C, MA and ME data
      if n < 6 then
         Put_Line("Enter " & Integer'Image(n) & " values for vector A");
         Enter_vec(A);
         Put_Line("Enter " & Integer'Image(n) & " values for vector B");
         Enter_vec(B);
         Put_Line("Enter " & Integer'Image(n) & " values for vector C");
         Enter_vec(C);
         Put_Line("Enter " & Integer'Image(n**2) & " values for matrix MA");
         Enter_Matr(MA);
         Put_Line("Enter " & Integer'Image(n**2) & " values for matrix ME");
         Enter_Matr(ME);
      else
         fill_vec(1, A);
         fill_vec(1, B);
         fill_vec(1, C);
         fill_Matr(1, MA);
         fill_Matr(1, ME);
         change_vec_value(A, 3, 17);
         change_matr_value(MA, 2, 4, 8);
      end if;
      
      --Calculation F1: d = (A * ((B + C) * (MA * ME)))
      delay 1.0;
      Func1(A, B, C, MA, ME, d);
      Put_Line("task T1 is finished");
   end T1;

   task T2 is
      pragma Priority(4);
      pragma Storage_Size(30000); --stack size
      pragma CPU(1);
   end T2;

   task body T2 is
      MF, MK, ML, MG: Matrix;
   begin
      Put_Line("task T2 is started");
      --Enter MF, MK and ML data
      if n < 6 then
         Put_Line("Enter " & Integer'Image(n**2) & " values for matrix MF");
         Enter_Matr(MF);
         Put_Line("Enter " & Integer'Image(n**2) & " values for matrix MK");
         Enter_Matr(MK);
         Put_Line("Enter " & Integer'Image(n**2) & " values for matrix ML");
         Enter_Matr(ML);
      else
         fill_Matr(1, MF);
         fill_Matr(1, MK);
         fill_Matr(1, ML);
         change_matr_value(MK, 3, 1, 21);
         change_matr_value(ML, 6, 5, 9);
      end if;
      
      --Calculation F2: MG = SORT(MF) * MK + ML
      delay 5.0;
      Func2(MF, MK, ML, MG);
      Put_Line("task T2 is finished");
   end T2;

   task T3 is
      pragma Priority(5);
      pragma Storage_Size(25000); --stack size
      pragma CPU(2);
   end T3;

   task body T3 is
      R, S, O: Vector;
      MT, MP: Matrix;
   begin
      Put_Line("task T3 is started");
      --Enter R, S, MT and MP data
      if n < 6 then
         Put_Line("Enter " & Integer'Image(n) & " values for vector R");
         Enter_vec(R);
         Put_Line("Enter " & Integer'Image(n) & " values for vector S");
         Enter_vec(S);
         Put_Line("Enter " & Integer'Image(n**2) & " values for matrix MT");
         Enter_Matr(MT);
         Put_Line("Enter " & Integer'Image(n**2) & " values for matrix MP");
         Enter_Matr(MP);
      else
         fill_vec(1, R);
         fill_vec(1, S);            
         fill_Matr(1, MT);
         fill_Matr(1, MP);
         change_vec_value(R, 2, 5);
         change_matr_value(MT, 1, 1, 3);
      end if;
      
      --Calculation F3: O = SORT(R + S) * (MT * MP)
      delay 2.9;
      Func3(R, S, MT, MP, O);
      Put_Line("task T3 is finished");
   end T3;

begin
   Put_Line("Lab1 is started");
end Lab1;
