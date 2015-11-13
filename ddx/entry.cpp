// khuangia@gmail.com
// code is free, but without any warranty!!!!

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <map>
#include <list>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <windows.h>
#include <ppl.h>

const char all_hero_name[][50] = {
	"shiwang",	
	"yangguo",
	"guojing",	
	"minmin",
	"duanhuangye",	
	"guangmingyoushi",
	"zhangwuji",
	"hongbangzhu",
	"qiuqianren",
	"chongyangzushi",
	"miejueshitai",
	"dongfangbubai",
	"zhangsanfeng",
	"jianmo",
	"dingtianyang",
	"jinzhulishi",
	"xiangzuoshi",
	"jiuyangdoujiu",
	"linghuchong",
	"feitianbianfu",
	"ouyangke",
	"xiaolongnv",
	"wudujiaozhu",
	"yuebuqun",
	"fenglaoqianbei",
	"zhouzhiruo",
	"fuwang",
	"yingwang",
	"huangdaozhu",
	"tiezhanglianhua",
	"yingying",
	"renjiaozhu",
	"mengguguoshi",
	"laoduwu",
	"laowantong",
	"zuomengzhu",
	"jiuyinhuangshang",
	"xuzhuzi",
	"meichaofeng",
	"qiuchuji",
	"xiaozhao",
	"chengkun",
	"huangrong",
	"lingongzi",
	"longwang",
	"mochou",
	"gumushizu",
	"xianger",
	"guangmingzuoshi",
	"jinguoxiaowangye",
	"duanyu",
	"wangyuyan",
	"qiaofeng"
};

static int get_hero_index(const char *hero_name) {

	for (int i = 0; i < _countof(all_hero_name); ++i) {
		if (0 == strcmp(hero_name, all_hero_name[i])) {
			return (i + 1);
		}	
	}

	printf ("fatal err: hero_name %s did not found\r\n", hero_name);
	exit(0);

	return -1;
}

static const char* get_hero_name(const int index) {

	for (int i = 0; i < _countof(all_hero_name); ++i) {
		if (index == (i + 1)) {
			return all_hero_name[i];
		}
	}

	printf ("fatal err: hero_id %d did not found\r\n", index);
	exit(0);

	return nullptr;
}

static std::size_t vector_hash(const std::vector<int> *vec) {
	
	std::size_t seed = 0;
	for (auto& i : (*vec)) {
		seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
	}

	return seed;
}

typedef struct hero_prop {
	int hero_index;

	int zs_t;
	int zs_d;
	int zs_r;

	int askhero_1;
	int askhero_2;
} hero_prop;

static int row_number(struct hero_prop *p) {

	if (p->hero_index < (18 + 1)) {
		return 1;
	}
	if (p->hero_index < (18 + 20 + 1)) {
		return 2;
	}
	else return 3;
}

const struct hero_prop all_hero_prop[] = {
	{get_hero_index("guojing"),			35, 45, 20, get_hero_index("feitianbianfu"),	get_hero_index("huangrong")},
	{get_hero_index("shiwang"),			 4, 80, 16, get_hero_index("zhangwuji"),		get_hero_index("yingwang")},
	{get_hero_index("minmin"),			11,  0, 89, get_hero_index("zhangwuji"),		get_hero_index("zhouzhiruo")},
	{get_hero_index("duanhuangye"),		 6, 17, 77, get_hero_index("huangdaozhu"),		get_hero_index("qiuqianren")},
	{get_hero_index("yangguo"),			10,  0, 91, get_hero_index("xiaolongnv"),		get_hero_index("xianger")},
	{get_hero_index("guangmingyoushi"), 72, 28,  0, get_hero_index("xiaozhao"),			get_hero_index("guangmingzuoshi")},
	{get_hero_index("zhangwuji"),		 0,  3, 97, get_hero_index("minmin"),			get_hero_index("zhouzhiruo")},
	{get_hero_index("hongbangzhu"),		80,  7, 13, get_hero_index("huangdaozhu"),		get_hero_index("huangrong")},
	{get_hero_index("qiuqianren"),		 0, 91,  9, get_hero_index("huangdaozhu"),		get_hero_index("tiezhanglianhua")},
	{get_hero_index("chongyangzushi"),	 0,100,  0, get_hero_index("huangdaozhu"),		get_hero_index("laowantong")},
	{get_hero_index("miejueshitai"),	 0, 91,  9, get_hero_index("zhangwuji"),		get_hero_index("zhouzhiruo")},
	{get_hero_index("dongfangbubai"),	40, 40, 40, get_hero_index("jiuyinhuangshang"), get_hero_index("zuomengzhu")},
	{get_hero_index("zhangsanfeng"),	 0,100,  0, get_hero_index("jiuyangdoujiu"),	get_hero_index("xianger")},
	{get_hero_index("jianmo"),			 0,120,  0, get_hero_index("jiuyangdoujiu"),	get_hero_index("fenglaoqianbei")},
	{get_hero_index("dingtianyang"),	 0, 0, 120, get_hero_index("zhangwuji"),		get_hero_index("shiwang")},
	{get_hero_index("jinzhulishi"),		 6,  0, 94, get_hero_index("xiaolongnv"),		get_hero_index("mengguguoshi")},
	{get_hero_index("xiangzuoshi"),		 0,  5, 95, get_hero_index("dongfangbubai"),	get_hero_index("linghuchong")},
	{get_hero_index("jiuyangdoujiu"),	40, 40, 40, get_hero_index("zhangsanfeng"),		get_hero_index("jiuyinhuangshang")},
	{get_hero_index("linghuchong"),		 0, 11, 89, get_hero_index("dongfangbubai"),	get_hero_index("fenglaoqianbei")},
	{get_hero_index("feitianbianfu"),	68, 32,  0, get_hero_index("guojing"),			get_hero_index("huangrong")},
	{get_hero_index("ouyangke"),		87,  3, 10, get_hero_index("guojing"),			get_hero_index("laoduwu")},
	{get_hero_index("xiaolongnv"),		24, 70,  6, get_hero_index("mochou"),			get_hero_index("yangguo")},
	{get_hero_index("wudujiaozhu"),		 0,  3, 97, get_hero_index("dongfangbubai"),	get_hero_index("xiangzuoshi")},
	{get_hero_index("yuebuqun"),		83, 17,  0, get_hero_index("dongfangbubai"),	get_hero_index("zuomengzhu")},
	{get_hero_index("fenglaoqianbei"),	120, 0,  0, get_hero_index("jianmo"),			get_hero_index("lingongzi")},
	{get_hero_index("zhouzhiruo"),		 5,  0, 95, get_hero_index("zhangwuji"),		get_hero_index("minmin")},
	{get_hero_index("fuwang"),			15, 85,  0, get_hero_index("xiaozhao"),			get_hero_index("minmin")},
	{get_hero_index("yingwang"),		13, 80,  7, get_hero_index("zhangwuji"),		get_hero_index("fuwang")},
	{get_hero_index("huangdaozhu"),		88,  0, 12, get_hero_index("meichaofeng"),		get_hero_index("laowantong")},
	{get_hero_index("tiezhanglianhua"),  0, 93,  7, get_hero_index("xiaolongnv"),		get_hero_index("qiuqianren")},
	{get_hero_index("yingying"),		 0, 15, 85, get_hero_index("xiaozhao"),			get_hero_index("linghuchong")},
	{get_hero_index("renjiaozhu"),		85,  0, 15, get_hero_index("dongfangbubai"),	get_hero_index("yuebuqun")},
	{get_hero_index("mengguguoshi"),	 0,  5, 95, get_hero_index("xiaolongnv"),		get_hero_index("xianger")},
	{get_hero_index("laoduwu"),			82, 18,  0, get_hero_index("huangdaozhu"),		get_hero_index("hongbangzhu")},
	{get_hero_index("laowantong"),		11,  6, 83, get_hero_index("huangdaozhu"),		get_hero_index("duanhuangye")},
	{get_hero_index("zuomengzhu"),		81, 19,  0, get_hero_index("dongfangbubai"),	get_hero_index("renjiaozhu")},
	{get_hero_index("jiuyinhuangshang"), 0,120,  0, get_hero_index("dongfangbubai"),	get_hero_index("jianmo")},
	{get_hero_index("xuzhuzi"),			120, 0,  0, get_hero_index("qiaofeng"),			get_hero_index("jiuyangdoujiu")},
	{get_hero_index("meichaofeng"),		90, 10,  0, get_hero_index("huangdaozhu"),		get_hero_index("huangrong")},
	{get_hero_index("qiuchuji"),		76,  9, 15, get_hero_index("guojing"),			get_hero_index("feitianbianfu")},
	{get_hero_index("xiaozhao"),		76, 15,  9, get_hero_index("guangmingzuoshi"),	get_hero_index("longwang")},
	{get_hero_index("chengkun"),		 0, 85, 15, get_hero_index("zhangwuji"),		get_hero_index("shiwang")},
	{get_hero_index("huangrong"),		44, 34, 22, get_hero_index("guojing"),			get_hero_index("laowantong")},
	{get_hero_index("lingongzi"),		33, 67,  0, get_hero_index("dongfangbubai"),	get_hero_index("linghuchong")},
	{get_hero_index("longwang"),		89,  0, 11, get_hero_index("xiaozhao"),			get_hero_index("guangmingyoushi")},
	{get_hero_index("mochou"),			54, 18, 28, get_hero_index("xiaolongnv"),		get_hero_index("tiezhanglianhua")},
	{get_hero_index("gumushizu"),		 0, 88, 12, get_hero_index("xiaolongnv"),		get_hero_index("chongyangzushi")},
	{get_hero_index("xianger"),			 6,  1, 93, get_hero_index("guojing"),			get_hero_index("jiuyangdoujiu")},
	{get_hero_index("guangmingzuoshi"), 79, 21,  0, get_hero_index("xiaozhao"),			get_hero_index("dingtianyang")},
	{get_hero_index("jinguoxiaowangye"), 80, 5, 15, get_hero_index("guojing"),			get_hero_index("meichaofeng")},
	{get_hero_index("duanyu"),			0, 120,  0, get_hero_index("xuzhuzi"),			get_hero_index("jianmo")},
	{get_hero_index("wangyuyan"),		40, 40, 40, get_hero_index("duanyu"),			get_hero_index("jianmo")},
};

static const hero_prop *get_hero_prop_byid(const int hero_id) {
	
	const int max_len = _countof(all_hero_prop);
	const hero_prop *pprop = nullptr;

	concurrency::parallel_for(0, max_len - 1, [&] (int i) {

		if (all_hero_prop[i].hero_index == hero_id) {
			pprop = (&all_hero_prop[i]);
		}
	});

	return pprop;
}

static const hero_prop *get_hero_prop(const char *name) {
	return get_hero_prop_byid(get_hero_index(name));	
}

typedef struct ref_hero_prop {

	const hero_prop *p;
	int size;

} ref_hero_prop, *pref_hero_prop;

typedef std::map<std::size_t, std::vector<int> *> hero_hash_data_vec;

typedef std::vector<int> hero_team_sub_t;
typedef std::vector<hero_team_sub_t *> hero_team_t;
typedef std::vector<hero_team_t *> hero_multeam_t;
typedef std::map<int, hero_multeam_t> hero_team_army_t;

namespace cs {

CRITICAL_SECTION print_lock;
CRITICAL_SECTION data_lock;
CRITICAL_SECTION opt_lock;

static double timetag_freq = 0;
static __int64 timetag_begin = 0;

static volatile long opt_sum = 0;
static volatile long opt_itor = 0;

inline void lock_increment(volatile long *n) {
	::InterlockedIncrement(n);
}

inline void lock_decrement(volatile long *n) {
	::InterlockedDecrement(n);
}

inline void lock_print() { ::EnterCriticalSection(&print_lock);	}
inline void lock_data() { ::EnterCriticalSection(&data_lock); }
inline void lock_opt() { ::EnterCriticalSection(&opt_lock); }
inline void release_print() { ::LeaveCriticalSection(&print_lock); }
inline void release_data() { ::LeaveCriticalSection(&data_lock); }
inline void release_opt() { ::LeaveCriticalSection(&opt_lock); }

inline void init_data() {
	::InitializeCriticalSection(&print_lock);
	::InitializeCriticalSection(&data_lock);
	::InitializeCriticalSection(&opt_lock);
	
	{
		LARGE_INTEGER li;
		if (!::QueryPerformanceFrequency(&li)) {
			return;
		}	

		timetag_freq = double(li.QuadPart) / 1000.0;

		::QueryPerformanceCounter(&li);
		timetag_begin = li.QuadPart;
	}
}

inline void cleanup_data() {
	::DeleteCriticalSection(&print_lock);
	::DeleteCriticalSection(&data_lock);
	::DeleteCriticalSection(&opt_lock);

	{
		LARGE_INTEGER li;
		::QueryPerformanceCounter(&li);
		double time_cost = double(li.QuadPart - timetag_begin) / timetag_freq;
		printf ("time cost: %d mili-sec\r\n", (int)time_cost);
	}
}

};

static void print_prop_arr(const hero_prop **prop_arr, int arr_siz, int addi) {

	cs::lock_print();
	printf ( "%d ", addi);

	for (int i = 0; i < arr_siz; ++i) {
		printf ( "%s-", get_hero_name(prop_arr[i]->hero_index));
	}

	printf ( "\r\n");
	cs::release_print();
}

static int get_xiayuan_num(const hero_prop **prop_arr, int arr_siz) {

	int xiayuan_num = 0;
	for (int i = 0; i < arr_siz; ++i) {
	
		const hero_prop *p = prop_arr[i];
		for (int j = 0; j < arr_siz; ++j) {
			
			if (i == j) continue;

			const hero_prop *p2 = prop_arr[j];
			if ((p->hero_index == p2->askhero_1) || (p->hero_index == p2->askhero_2)) {
				++xiayuan_num;
			}
		}
	}

	return xiayuan_num;
}

enum {
	zstype_hun,
	zstype_tian,
	zstype_big_tian,
	zstype_di,
	zstype_big_di,
	zstype_ren,
	zstype_big_ren,
	zstype_big_hun,
	zstype_endtag
};

static const char *get_zstype_desc(int zs_type) {

	static const char *desc[] = {
		"xiaohunyuan",
		"xiaotian",
		"datian",
		"xiaodi",
		"dadi",
		"xiaoren",
		"daren",
		"dahunyuan"	
	};

	if ((zs_type >= zstype_endtag) || (zs_type < zstype_hun)) {
		printf ("fatal err: %d cannot find zstype\r\n", zs_type);
		exit(0);
	}

	return desc[zs_type];
}

static int get_zs_type(const hero_prop **prop_arr, int arr_siz, double& t, double& d, double& r) {

	int zs_type = zstype_hun;
	t = d = r = 0;

	double d_all = 0, r_all = 0, t_all = 0;

	for (int i = 0; i < arr_siz; ++i) {
		t_all += prop_arr[i]->zs_t;
		d_all += prop_arr[i]->zs_d;
		r_all += prop_arr[i]->zs_r;
	}

	double n_all = t_all + d_all + r_all;

	t = t_all / n_all;
	d = d_all / n_all;
	r = r_all / n_all;

	if (t > 0.70) {
		zs_type = zstype_big_tian;
	}
	else if (d > 0.70) {
		zs_type = zstype_big_di;
	}
	else if (r > 0.70) {
		zs_type = zstype_big_ren;
	}
	else if ((d > 0.5) && (d < 0.71)) {
		zs_type = zstype_di;
	}
	else if ((t > 0.5) && (t < 0.71)) {
		zs_type = zstype_tian;
	}
	else if ((r > 0.5) && (r < 0.71)) {
		zs_type = zstype_ren;
	}	
	else if ((t > 0.32) && (t < 0.34) && (d > 0.32) && (d < 0.34) && (r > 0.32) && (r < 0.34)) {
		zs_type = zstype_big_hun;
	}
	else {
		zs_type = zstype_hun;
	}

	return zs_type;
}

static bool save_vec_isexists(hero_hash_data_vec* vec, const hero_prop **arr, int arr_siz) {

	auto v1 = new std::vector<int>();
	for (int i = 0; i < arr_siz; ++i) v1->push_back(arr[i]->hero_index);

	std::sort(v1->begin(), v1->end(), std::less<int>());
	std::size_t vh = vector_hash(v1);

	cs::lock_data();
	if (vec->end() != vec->find(vh)) {		
		cs::release_data();
		return true;
	}

	(*vec)[vh] = v1;
	cs::release_data();
	return false;
}

static void save_vec_direct(hero_hash_data_vec* vec, const hero_prop **arr, int arr_siz) {

	auto v1 = new std::vector<int>();
	for (int i = 0; i < arr_siz; ++i) v1->push_back(arr[i]->hero_index);

	std::sort(v1->begin(), v1->end(), std::less<int>());

	cs::lock_data();
	(*vec)[vector_hash(v1)] = v1;
	cs::release_data();
}

static bool opt_is_exists(hero_hash_data_vec* vec, const hero_prop **arr, int arr_siz) {
		
	auto v1 = new std::vector<int>();
	for (int i = 0; i < arr_siz; ++i) v1->push_back(arr[i]->hero_index);

	std::sort(v1->begin(), v1->end(), std::less<int>());
	std::size_t vh = vector_hash(v1);

	cs::lock_opt();
	if (vec->end() != vec->find(vh)) {		
		cs::release_opt();
		return true;
	}

	(*vec)[vector_hash(v1)] = v1;
	cs::release_opt();
	return false;
}

static void free_vec(hero_hash_data_vec* vec) {

	for (auto& vi : (*vec)) {
		delete vi.second;
	}

	vec->clear();
}

static unsigned __stdcall show_progress(void *p) {

	auto evt = (HANDLE)p;
	while (WAIT_OBJECT_0 != ::WaitForSingleObject(evt, 200)) {
		
		double val = (double)cs::opt_itor / (double)cs::opt_sum;
		printf ("progress: %.1f", val);	
	}
}

struct walk_tree_struct {
	const int max_layer_num;
	const hero_prop **prop_arr;
	int layer_num;
	int xynum;
};

static void walk_asking_tree(const hero_prop *hd1, walk_tree_struct *pst) {
	
	// walk the tree, enter to the last layer, print result
	// then go back, layer_num reduce, trim prop_arr base on layer_num
	// how many layer_num, how many prop_arr
	// then keep going to walk the tree, to the last layer, print result
	// then go back, keep running till back to the first layer

	++pst->layer_num;
	++pst->xynum;

	pst->prop_arr[pst->layer_num - 1] = hd1;	
	// xy num update

	if (pst->layer_num >= pst->max_layer_num) {
		return;
	}

	walk_asking_tree(get_hero_prop_byid(hd1->askhero_1), pst);
	
	walk_asking_tree(get_hero_prop_byid(hd1->askhero_2), pst);
}

#define define_find_heros_callback(name) \
	static void __cdecl name(const hero_prop **prop_arr, const int arr_siz, void *data)

static void find_heros_intree(
	void (__cdecl *pfn_callback)(const hero_prop **ph, const int phsiz, void *data), 
	pref_hero_prop p, 
	void *data) {

	concurrency::parallel_for(0, (p->size - 1), [&] (int i1) {
		walk_tree_struct wts = {
			5, (const hero_prop **)malloc(5 * sizeof(hero_prop *)), 0, 0};

		walk_asking_tree(&p->p[i1], &wts);

		free(wts.prop_arr);
	});
}

static void find_heros_enum(
	void (__cdecl *pfn_callback)(const hero_prop **ph, const int phsiz, void *data), 
	pref_hero_prop p, 
	void *data) {

	auto poptvec = new hero_hash_data_vec();

	concurrency::parallel_for(0, (p->size - 1), [&] (int i1) {

	const hero_prop *hd1 = &p->p[i1];
	concurrency::parallel_for(0, (p->size - 1), [&] (int i2) {
		
	const hero_prop *hd2 = &p->p[i2];
	if (hd1->hero_index != hd2->hero_index) 
	concurrency::parallel_for(0, (p->size - 1), [&] (int i3) {
				
	const hero_prop *hd3 = &p->p[i3];
	if ((hd2->hero_index != hd3->hero_index) && 
		(hd1->hero_index != hd3->hero_index))
	concurrency::parallel_for(0, (p->size - 1), [&] (int i4) {

	const hero_prop *hd4 = &p->p[i4];
	if ((hd1->hero_index != hd4->hero_index) && 
		(hd2->hero_index != hd4->hero_index) && 
		(hd3->hero_index != hd4->hero_index))
	concurrency::parallel_for(0, (p->size - 1), [&] (int i5) {
					
		const hero_prop *hd5 = &p->p[i5];
		if ((hd1->hero_index != hd5->hero_index) && 
			(hd2->hero_index != hd5->hero_index) && 
			(hd3->hero_index != hd5->hero_index) &&
			(hd4->hero_index != hd5->hero_index)) {

			const hero_prop* prop_arr[] = {hd1, hd2, hd3, hd4, hd5};
			const int arr_siz = _countof(prop_arr);

			pfn_callback(prop_arr, arr_siz, data);
		}

	});});});});});

	free_vec(poptvec);
	delete poptvec;
}

typedef struct callback_struct {
	hero_hash_data_vec *pvec;
	bool print_result;
	int addi;
	int addi2;
} callback_struct;

define_find_heros_callback(callback_xiayuan_tops) {
	
	auto p = (callback_struct *)data;
	int min_xy = p->addi;

	int xynum = get_xiayuan_num(prop_arr, arr_siz);
	if (xynum >= min_xy) {
		
		if (!save_vec_isexists(p->pvec, prop_arr, arr_siz)) {
			if (p->print_result) print_prop_arr(prop_arr, arr_siz, xynum);
		}
	}	
}

define_find_heros_callback(callback_zhuashu_tops) {
		
	auto p = (callback_struct *)data;
	int zs_type = p->addi;
	int zs_val = p->addi2;

	double t = 0, d = 0, r = 0;

	int ret_zs_type = get_zs_type(prop_arr, arr_siz, t, d, r);
	if (ret_zs_type == zs_type) {
		//
		// skip zhuanshu value first
		//
		if (!save_vec_isexists(p->pvec, prop_arr, arr_siz)) {

			if (p->print_result) print_prop_arr(prop_arr, arr_siz, zs_type);
		}
	}
}

int get_hero_num(const hero_team_sub_t *t, const hero_team_sub_t *d, const hero_team_sub_t *h) {

	std::map<int, int> tmp;

	for (auto& i : *t) tmp[i] = 1;
	for (auto& i : *d) tmp[i] = 1;
	for (auto& i : *h) tmp[i] = 1;
	
	return tmp.size();
}

define_find_heros_callback(callback_bigall_tops) {

	
}

define_find_heros_callback(callback_xiayuanzhuanshu_tops) {
	
	auto p = (callback_struct *)data;
	int min_xy = p->addi;
	int zs_type = p->addi2;
			
	int xynum = get_xiayuan_num(prop_arr, arr_siz);
	if (xynum >= min_xy) {
	
		double t = 0, d = 0, r = 0;
		int ret_zs_type = get_zs_type(prop_arr, arr_siz, t, d, r);
		if (ret_zs_type == zs_type) {
		
			if (!save_vec_isexists(p->pvec, prop_arr, arr_siz)) {
				
				if (p->print_result) print_prop_arr(prop_arr, arr_siz, xynum);
			}
		}
	}
}

static void __cdecl test_hero_combo(const hero_prop **prop_arr, const int arr_siz, void *data) {
	
	double t = 0, d = 0, r = 0;

	int ret_zs_type = get_zs_type(prop_arr, arr_siz, t, d, r);
	printf ("zhuanshu type: %s (%.3f-%.3f-%.3f)\r\n", get_zstype_desc(ret_zs_type), t, d, r);

	int xynum = get_xiayuan_num(prop_arr, arr_siz);
	printf ("xiayuan num: %d\r\n", xynum);

	print_prop_arr(prop_arr, arr_siz, xynum);
}

static void test_data_correct() {
	
	for (int i = 0; i < _countof(all_hero_prop); ++i) {
	
		auto p = all_hero_prop[i];
		int sum_zs = p.zs_d + p.zs_t + p.zs_r;

		if (sum_zs < 100) {
			printf ("fatal err: %s, data incruupt\r\n", get_hero_name(p.hero_index));
			exit(0);
		}
	}

	return;

}

static void read_data_from_streram(std::ifstream& file, hero_team_t& outb) {

	std::string buf;
	while (std::getline(file, buf)) {
	
		if (buf[1] != ' ') continue;

		auto item = new hero_team_sub_t();

		buf.erase(buf.begin(), buf.begin() + 2);
		buf.erase(buf.end() - 2, buf.end());

		std::istringstream fstr(buf.c_str());
		
		std::string subs;
		while (std::getline(fstr, subs, '-')) {
			item->push_back(get_hero_index(subs.c_str()));
		}
		
		outb.push_back(item);
	}
}

std::map<int, int> filtered_map;

static void filter_init() {

	const char filtered_names[][50] = {

		"dingtianyang",
		"jiuyangdoujiu",
		"dongfangbubai",
		"jiuyinhuangshang",
		"jianmo",
		"zhangsanfeng",
		"xuzhuzi",
		"fenglaoqianbei",
		"xuzhuzi",
		"duanyu",

		"qiuqianren",
		"ouyangke",
		"longwang",
		"xiaozhao",
		"zhangwuji",
		"chongyangzushi",
		"gumushizu",
		"miejueshitai",
		"minmin",
		"yangguo"
	};

	for (int i = 0; i < _countof(filtered_names); ++i) {
		filtered_map[get_hero_index(filtered_names[i])] = 1;
	}
}

static bool filter_team_sub(hero_team_sub_t *vi) {

	for (auto& i : *vi) {
		if (filtered_map.end() != filtered_map.find(i)) return true;
	}
	return false;
}

static void test_less_num_combo(int max_num) {

	std::ifstream 
		if_tian("F:\\cmake\\ddx\\Release\\d42.txt"),
		if_di("F:\\cmake\\ddx\\Release\\d44.txt"),
		if_hun("F:\\cmake\\ddx\\Release\\d47.txt");

	hero_team_t vec_tian, vec_di, vec_hun;

	read_data_from_streram(if_tian, vec_tian);
	if_tian.close();

	read_data_from_streram(if_di, vec_di);
	if_di.close();

	read_data_from_streram(if_hun, vec_hun);
	if_hun.close();
	
	hero_team_army_t result_map;

	filter_init();
	
	concurrency::parallel_for_each(vec_tian.begin(), vec_tian.end(), [&] (hero_team_sub_t *itian) {

		if (!filter_team_sub(itian)) {

		concurrency::parallel_for_each(vec_di.begin(), vec_di.end(), [&] (hero_team_sub_t *idi) {
		
			if (!filter_team_sub(idi)) {
			
			concurrency::parallel_for_each(vec_hun.begin(), vec_hun.end(), [&] (hero_team_sub_t *ihun) {
	
				if (!filter_team_sub(ihun)) {

				int num = get_hero_num(itian, idi, ihun);
				if (num <= max_num) {
				
					auto hero_team = new hero_team_t();
					hero_team->push_back(itian);
					hero_team->push_back(idi);
					hero_team->push_back(ihun);

					cs::lock_data();
					result_map[num].push_back(hero_team);
					cs::release_data();
				}
				}
			});
			}
		});
		}
	});

	for (auto& mul_team_i : result_map) {
		printf ("num: %d, total: %d\r\n", mul_team_i.first, mul_team_i.second.size());
		for (auto& team_i : mul_team_i.second) {

			std::map<int, int> tmp_team;
			for (auto& team_sub_i : *team_i) {							
				for (auto& i : *team_sub_i) {
					tmp_team[i] = 1;
				}
			}

			for (auto& i : tmp_team) {
				printf ("%s-", get_hero_name(i.first));
			}

			printf("\r\n");
		}	
	}

	for (auto& mul_team_i : result_map) {	
		for (auto& team_i : mul_team_i.second) {
			for (auto& team_sub_i : *team_i) {			
			}
			delete team_i;
		}	
	}
}

static bool test_before_all() {

	test_data_correct();
	return false;

	//"xiangzuoshi", "dongfangbubai", "linghuchong", "longwang", "xiaozhao"
	//"guojing", "huangrong", "xiaolongnv", "xianger", "mochou"
	//"shiwang", "guojing", "feitianbianfu", "xiaolongnv", "huangrong"

	char *test_arr[5] = {
	"shiwang", "guojing", "feitianbianfu", "xiaolongnv", "huangrong"
	};

	const hero_prop* prop_arr[] = {
		get_hero_prop(test_arr[0]), get_hero_prop(test_arr[1]), get_hero_prop(test_arr[2]), 
		get_hero_prop(test_arr[3]), get_hero_prop(test_arr[4])
	};

	const int arr_siz = _countof(prop_arr);
	test_hero_combo(prop_arr, arr_siz, nullptr);

	return true;
}

static void usage() {
	printf (
		"\r\n"
		"from khuangia@gmail, but without any warranty!!\r\n"
		"usage: \r\n"
		"    ddx -tt huangrong guojing qiuchuji feitianbianfu xiaozhao\r\n"
		"    ddx -xy 7     get xiayuan equal or big than 7 combo\r\n"
		"    ddx -zs 110   get zhuanshu tian 71per\r\n"
		"            0 zstype_hun\r\n"
		"            1 zstype_tian\r\n"
		"            2 zstype_big_tian\r\n"
		"            3 zstype_di\r\n"
		"            4 zstype_big_di\r\n"
		"            5 zstype_ren\r\n"
		"            6 zstype_big_ren\r\n"
		"            7 zstype_big_hun\r\n"
		"            use 0-7 as prefix, then follow 10, donot ask me why\r\n"
		"    ddx -zs 251   get zhuanshu di 51per, hun only have 33per, no other\r\n"
		"    ddx -zx 5 171 get zhuanshu tian 71per and xiayuan more than 5\r\n"
		"    ddx -k 12"
		"\r\n");
}

void main(int argc, char *argv[]) {

	cs::init_data();

	if (test_before_all()) {
		cs::cleanup_data();
		return;
	}

	if ((argc != 7) && ((argc > 4) || (argc < 2))) {
		usage();
	}
	else {
		const char *cm = argv[1];
		if (cm[0] != '-') usage();
		else {
			if ((cm[1] == 't') && (cm[2] == 't')) {
				if (argc != 7) usage();
				else {
					const hero_prop* prop_arr[] = {
						get_hero_prop(argv[2]), get_hero_prop(argv[3]), get_hero_prop(argv[4]), 
						get_hero_prop(argv[5]), get_hero_prop(argv[6])
					};

					const int arr_siz = _countof(prop_arr);
					test_hero_combo(prop_arr, arr_siz, nullptr);					
				}
			}
			else if ((cm[1] == 'x') && (cm[2] == 'y')) {
				if (argc != 3) usage();
				else {
					const char *xyn = argv[2];
					int nxy = strtol(xyn, '\0', 10);
					if (nxy < 0) usage();
					else {
						hero_hash_data_vec vec;

						ref_hero_prop refp;
						refp.p = all_hero_prop;
						refp.size = _countof(all_hero_prop);

						callback_struct st = {&vec, true, nxy, 0};
						find_heros_enum(&callback_xiayuan_tops, &refp, &st);

						free_vec(&vec);
					}
				}
			}
			else if (cm[1] == 'z') {
				if (cm[2] == 's') {
					if (argc != 3) usage();
					else {
						const char *zsn = argv[2];

						char tonsz[3] = {zsn[0], '\0', '\0'};
						int zstype = strtol(tonsz, '\0', 10);

						if (zstype > zstype_endtag) {
							usage();
						}
						else {						
							char szsn[20] = {0};
							strncpy(szsn, zsn, 18);
							
							int zsval = strtol(szsn + 1, '\0', 10);
							if (zsval < 0) usage();
							else {
								hero_hash_data_vec vec;

								ref_hero_prop refp;
								refp.p = all_hero_prop;
								refp.size = _countof(all_hero_prop);
	
								callback_struct st = {&vec, true, zstype, zsval};
								find_heros_enum(&callback_zhuashu_tops, &refp, &st);
								
								free_vec(&vec);
							}
						}
					}
				}
				else if (cm[2] == 'x') {
					if (argc != 4) usage();
					else {
						const char *xyn = argv[2];
						const int nxy = strtol(xyn, '\0', 10);

						if (nxy < 0) usage();
						else {
							const char *zsn = argv[3];
							const char tonsz[3] = {zsn[0], '\0', '\0'};
							const int zstype = strtol(tonsz, '\0', 10);

							if (zstype > zstype_endtag) {
								usage();
							}
							else {						
								char szsn[20] = {0};
								strncpy(szsn, zsn, 18);
							
								int zsval = strtol(szsn + 1, '\0', 10);
								if (zsval < 0) usage();
								else {
									hero_hash_data_vec vec;

									ref_hero_prop refp;
									refp.p = all_hero_prop;
									refp.size = _countof(all_hero_prop);
	
									callback_struct st = {&vec, true, nxy, zstype};
									find_heros_enum(&callback_xiayuanzhuanshu_tops, &refp, &st);
								
									free_vec(&vec);
								}
							}
						}
					}
				}
				else {
					usage();
				}
			}
			else if (cm[1] == 'k') {
				if (argc != 3) usage();
				else {
					const char *xyn = argv[2];
					const int nxy = strtol(xyn, '\0', 10);
					test_less_num_combo(nxy);
				}
			}
			else usage();
		}
	}

	cs::cleanup_data();
}
















