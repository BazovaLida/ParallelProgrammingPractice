--Basics Of Parallel Programming
--"Semaphores in ADA"
--Bazova L.
--IV-81
--Date: 12.02.2020
--main.abd file


with Ada.Text_IO, Ada.Integer_Text_IO;
use Ada.Text_IO, Ada.Integer_Text_IO;
with Semaphore;
use Semaphore;

procedure main is


   SemExc: SIMA(1, 1); --Semaphore for exception task
   SemSynch: SeveralTasksSynch(2, 0); --Semaphore for synchronisation task

   numb1: Integer;
   numb2: Integer;
   task Enter1;
   task Enter2;
   task AddTask;
   task SubTask;

   task body Enter1 is
   begin
      SemExc.P;
      Put_Line("Enter the first number for mathematical operations");
      Get(numb1);
      SemExc.V;
      SemSynch.V;
   end Enter1;

   task body Enter2 is
   begin
      SemExc.P;
      Put_Line("Enter the second number for mathematical operations");
      Get(numb2);
      SemExc.V;
      SemSynch.V;
   end Enter2;

   task body AddTask is
      sum: Integer;
   begin
      SemSynch.P;
      sum := numb1 + numb2;
      SemExc.P;
      Put_Line("The sum of numbers is" & Integer'Image(sum));
      SemExc.V;
   end AddTask;

   task body SubTask is
      sub: Integer;
   begin
      SemSynch.P;
      sub := numb1 - numb2;
      SemExc.P;
      Put_Line("The residual of numbers is" & Integer'Image(sub));
      SemExc.V;
   end SubTask;

begin
   null;
end main;
