--Basics Of Parallel Programming
--"Semaphores in ADA"
--Bazova L.
--IV-81
--Date: 12.02.2020
--Semaphore.abd file

package body Semaphore is

   protected body SIMA is
      entry P when S > 0 is
      begin
         S := S - 1;
      end P;
      entry V when S < MaxCount is
      begin
         S := S + 1;
      end V;
   end SIMA;

   protected body SeveralTasksSynch is
      entry P when F=count is
         begin
         null;
      end P;
      procedure V is
      begin
         F := F + 1;
      end V;
   end SeveralTasksSynch;

end Semaphore;
