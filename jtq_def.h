/* size */
#define LEN 1024
/* type */
/** node **/
#define NdType_Dict 1
#define NdType_Arr 2
#define NdType_KV 4
#define NdType_Key 8
#define NdType_Val 16
#define NdType_Cj 32	// コンジュゲータ
/** conjugator **/
// for NdType_Cj	// 後続のNdにセット => NdType
#define CjType_C 256	// ","
#define CjType_D 512	// "{"
#define CjType_A 1024	// "["
/** close **/		// 自身のNdにセット => NdType
#define ClType_Dc 2048	// "}"
#define ClType_Ac 4096	// "]"
