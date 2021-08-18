--Basics Of Parallel Programming
--"Semaphores in ADA"
--Bazova L.
--IV-81
--Date: 12.02.2020
--Semaphore.abs file

package Semaphore is

   protected type SIMA(Max: Natural; Initial: Natural)  is
      entry P;
      entry V;
   private
      MaxCount : Natural := Max;
      S : Natural := Initial;
   end SIMA;

   protected Type SeveralTasksSynch(NeededTasks: Natural; Initial: Natural) is
      entry P;
      procedure V;
   private
      Count: Natural := NeededTasks;
      F: Natural := 0;
   end SeveralTasksSynch;

end Semaphore;
