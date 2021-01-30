// Listado 3.10 Convay's Game of Live

while (gens -- > 0) {
  #pragma omp parallel for collapse (2)
    for (int i = 0; i < size; i++)
      for (int j = 0; j < size; j++) {
        int neighs = neighbors (plane , size , i, j);
        switch (plane[i][j]) {
          case 0: aux_plane[i][j] = (neighs == 3);
            break;
          case 1: aux_plane[i][j] = (neighs == 2) || (neighs == 3);
            break;
        }
      }
  char **tmp_plane = aux_plane; aux_plane = plane; plane = tmp_plane;
}
