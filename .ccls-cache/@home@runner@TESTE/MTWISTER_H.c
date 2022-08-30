# ifndef __MTWISTER_H
# define  __MTWISTER_H

# define  STATE_VECTOR_LENGTH  624
# define  STATE_VECTOR_M       397  /* mudanças para STATE_VECTOR_LENGTH também requerem mudanças para isso */

typedef  struct tagMTRand {
   mt longo não assinado [STATE_VECTOR_LENGTH];
   índice inteiro ;
} MTRand;

MTR e seedRand ( semente longa não assinada  );
genRandLong  longo não assinado (  MTRand * rand);
duplo  genRand (MTRand* rand);

# endif  /* #ifndef __MTWISTER_H */