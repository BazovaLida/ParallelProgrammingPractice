namespace Parallel_Programing_c_sharp.Data
{
    public class Data
    {
        private readonly int _size;

        public Data(int sizeGiven)
        {
            _size = sizeGiven;
        }

        //F1: d = (A * ((B + C) * (MA * ME)))
        private int d;
        private int[] A, B, C;
        private int[,] MA, ME;

        public void F1_input(int c)
        {
            A = get_vec_with(c);
            B = get_vec_with(c);
            C = get_vec_with(c);
            MA = get_matrix_with(c);
            ME = get_matrix_with(c);
        }

        public void F1_calc()
        {
            //constant for
            int[,] MD1 = multiply_matrix(MA, ME);
            int[] D2 = sum_vec(B, C);
            int[] D3 = multiply_vec_matrix(D2, MD1);
            d = scalar_multiply_vec(A, D3);
        }

        public int F1_result()
        {
            return d;
        }

        //F2: MG = SORT(MF) * MK + ML
        private int[,] MF, MK, ML, MG;

        public void F2_input(int c)
        {
            MF = get_matrix_with(c);
            MK = get_matrix_with(c);
            ML = get_matrix_with(c);
        }

        public void F2_calc()
        {
            int[,] MD1 = sort_matrix(MF);
            int[,] MD2 = multiply_matrix(MD1, MK);
            MG = sum_matrix(MD2, ML);
        }

        public int[,] F2_result()
        {
            return MG;
        }

        //F3: O = SORT(R + S) * (MT * MP)
        private int[] R, S, O;
        private int[,] MT, MP;

        public void F3_input(int c)
        {
            R = get_vec_with(c);
            S = get_vec_with(c);
            MT = get_matrix_with(c);
            MP = get_matrix_with(c);
        }

        public void F3_calc()
        {
            int[] D1 = sum_vec(R, S);
            int[] D2 = sort_vec(D1);
            int[,] MD3 = multiply_matrix(MT, MP);
            O = multiply_vec_matrix(D2, MD3);
        }

        public int[] F3_result()
        {
            return O;
        }

        private int[,] multiply_matrix(int[,] MA, int[,] MB)
        {
            int[,] MT = new int[_size, _size];
            for (int k = 0; k < _size; k++)
            {
                for (int i = 0; i < _size; i++)
                {
                    MT[k, i] = 0;
                    for (int j = 0; j < _size; j++)
                    {
                        MT[k, i] += +MA[k, j] * MB[j, i];
                    }
                }
            }

            return MT;
        }

        private int[] multiply_vec_matrix(int[] V, int[,] MA)
        {
            int m;
            int[] R = new int[_size];
            for (int i = 0; i < _size; i++)
            {
                m = 0;
                for (int j = 0; j < _size; j++)
                {
                    m += V[i] * MA[j, i];
                }

                R[i] = m;
            }

            return R;
        }

        private int[] sum_vec(int[] A, int[] B)
        {
            for (int i = 0; i < _size; i++)
            {
                A[i] += B[i];
            }

            return A;
        }

        private int[,] sum_matrix(int[,] MA, int[,] MB)
        {
            for (int i = 0; i < _size; i++)
            {
                for (int j = 0; j < _size; j++)
                {
                    MA[i, j] += MB[i, j];
                }
            }

            return MA;
        }

        private int scalar_multiply_vec(int[] A, int[] B)
        {
            int t = 0;
            for (int i = 0; i < _size; i++)
            {
                t += A[i] + B[i];
            }

            return t;
        }

        private int[,] sort_matrix(int[,] MA)
        {
            int t; // temporary
            for (int i = 0; i < _size; i++)
            {
                for (int j = _size - 1; j >= 0; j--)
                {
                    for (int k = 1; k < j; k++)
                    {
                        if (MA[i, k] < MA[i, k + 1])
                        {
                            t = MA[i, k];
                            MA[i, k] = MA[i, k + 1];
                            MA[i, k + 1] = t;
                        }
                    }
                }
            }

            return MA;
        }

        private int[] sort_vec(int[] V)
        {
            int t;
            for (int i = 0; i < _size; i++)
            {
                for (int j = 0; j < _size; j++)
                {
                    if (V[i] > V[j])
                    {
                        t = V[j];
                        V[j] = V[i];
                        V[i] = t;
                    }
                }
            }

            return V;
        }

        private int[] get_vec_with(int c)
        {
            int[] V = new int[_size];
            for (int i = 0; i < _size; i++)
            {
                V[i] = c;
            }

            return V;
        }

        private int[,] get_matrix_with(int c)
        {
            int[,] MA = new int[_size, _size];
            for (int i = 0; i < _size; i++)
            {
                for (int j = 0; j < _size; j++)
                {
                    MA[i, j] = c;
                }
            }

            return MA;
        }
    }
}