/*
 * Copyright (c) 2018-2021 The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/version.h>
#include <net/sock.h>
#include <linux/netlink.h>
#include <linux/ip.h>
#include <linux/ipv6.h>
#include <linux/cpu.h>
#include <linux/oom.h>
#include <net/ip.h>
#include <linux/bitmap.h>
#include <linux/netdevice.h>
#include <linux/kernel.h>
#include <linux/smp.h>
#include <linux/percpu-defs.h>
#include <linux/module.h>
#include <linux/cpumask.h>

#include "rmnet_shs.h"
#include "rmnet_shs_config.h"
#include "rmnet_shs_wq.h"
#include "rmnet_shs_modules.h"
#include "rmnet_shs_common.h"

/* Forward declaration for the notifier function to resolve ordering issue */
static int DATARMNET2aa4ef6ff9(struct notifier_block *nb, unsigned long event, void *ptr);

/* Obfuscated Defines */
#define DATARMNET2f67183a86 2000000
#define DATARMNET68fc0be252 1000000
#define DATARMNETd391fbd694 0
#define DATARMNETae2e980d66 1
#define DATARMNET249a927510 10
#define DATARMNET904145ccb9 1
#define DATARMNETb91aee91fd -1
#define DATARMNET00d5787aad 2000000
#define DATARMNET8948dc953d 10
#define DATARMNET20dc6bb36b 1
#define DATARMNET832731a933(CPU) (per_cpu(softnet_data, CPU).input_pkt_queue)
#define DATARMNET3de2536baf(CPU) (per_cpu(softnet_data, CPU).process_queue)
#define DATARMNET78ec5e8746(var, CPU) (per_cpu(var, CPU).input_queue_tail)
#define DATARMNET9c1c20df35(var, CPU) (per_cpu(var, CPU).input_queue_head)
#define DATARMNETba5ea4329f(CPU) DATARMNETecc0627c70.DATARMNET132b9c7dc4[CPU].DATARMNET758a55f103
#define DATARMNETec970d7090 1
#define DATARMNET8fadb49f38 0
#define DATARMNET48a89fcc16 1
#define DATARMNETbfe901fc62 0

/* Global variables */
DEFINE_SPINLOCK(DATARMNET3764d083f0);
DEFINE_HASHTABLE(DATARMNETe603c3a4b3, DATARMNET25437d35fd);
struct DATARMNETe600c5b727 DATARMNET0997c5650d[DATARMNETc6782fed88];
int DATARMNETcff375d916[DATARMNETc6782fed88];
struct DATARMNETa6b20d7e8b DATARMNETecc0627c70;
struct DATARMNET37ef896af8 shs_rx_work;

/* Module parameter */
unsigned int DATARMNETaf998640fd __read_mostly = 1000;
module_param(DATARMNETaf998640fd, int, 0644);
MODULE_PARM_DESC(DATARMNETaf998640fd, "Max qmap backlog");

/* Notifier block definition */
static struct notifier_block DATARMNET105c85d84c = {
	.notifier_call = DATARMNET2aa4ef6ff9,
};

#if LINUX_VERSION_CODE >= KERNEL_VERSION(5, 4, 0)
ssize_t DATARMNET713da9913c(struct netdev_rx_queue *rxq, u8 cpu, u8 calling_cpu, u8 is_gro)
{
	/* rps_map and related logic removed for kernel 5.4+ */
	return 0;
}
#else
ssize_t DATARMNET713da9913c(struct netdev_rx_queue*DATARMNETb4180393e4,u8 cpu,u8 DATARMNETa7a5705ab0,u8 DATARMNET5780499e9c)
{
    struct rps_map *DATARMNETaeb4918e65, *map;
    cpumask_var_t mask;
    int DATARMNET421230d879;
    if(!DATARMNET5780499e9c && (DATARMNET3de2536baf(DATARMNETa7a5705ab0).qlen & DATARMNET832731a933(DATARMNETa7a5705ab0).qlen))
        return -1;
    map = rcu_dereference(DATARMNETb4180393e4->rps_map);
    if (map) {
        map->cpus[0] = cpu;
        map->len = 1;
        DATARMNET421230d879 = (DATARMNET3de2536baf(DATARMNETa7a5705ab0).qlen + DATARMNET832731a933(DATARMNETa7a5705ab0).qlen);
        if (DATARMNET421230d879 && DATARMNETecc0627c70.DATARMNET7d667e828e != DATARMNETecc0627c70.DATARMNET5c24e1df05) {
            DATARMNET68d84e7b98[DATARMNETfeaf903a28]++;
            DATARMNET4bde88919f(DATARMNETa7a5705ab0, DATARMNET421230d879);
        }
        return 0;
    }
    if (!alloc_cpumask_var(&mask, GFP_ATOMIC))
        return -ENOMEM;
    cpumask_set_cpu(cpu, (struct cpumask*)&mask);
    map = kzalloc(max_t(unsigned int, RPS_MAP_SIZE(cpumask_weight(mask)), L1_CACHE_BYTES), GFP_ATOMIC);
    if (!map) {
        free_cpumask_var(mask);
        return -ENOMEM;
    }
    map->cpus[0] = cpu;
    map->len = 1;
    rcu_read_lock();
    DATARMNETaeb4918e65 = rcu_dereference(DATARMNETb4180393e4->rps_map);
    rcu_assign_pointer(DATARMNETb4180393e4->rps_map, map);
    if (DATARMNETaeb4918e65)
        kfree(DATARMNETaeb4918e65);
    free_cpumask_var(mask);
    rcu_read_unlock();
    DATARMNET421230d879 = (DATARMNET3de2536baf(DATARMNETa7a5705ab0).qlen + DATARMNET832731a933(DATARMNETa7a5705ab0).qlen);
    if (DATARMNET421230d879 && DATARMNETecc0627c70.DATARMNET7d667e828e != DATARMNETecc0627c70.DATARMNET5c24e1df05) {
        DATARMNET68d84e7b98[DATARMNETfeaf903a28]++;
    }
    return 0;
}
#endif

static void* DATARMNETefcaf5fbe9(struct sk_buff*skb, u32 offset, u32 len, void*buf)
{
    struct skb_shared_info*shinfo = skb_shinfo(skb);
    skb_frag_t*frag;
    u32 frag_offset = offset;
    int i;

    if (offset > skb->len || len > skb->len || offset + len > skb->len)
        return NULL;

    if (skb_headlen(skb) >= offset + len)
        return skb->data + offset;

    offset -= skb_headlen(skb);
    for (i = 0; i < shinfo->nr_frags; i++) {
        u32 frag_size;
        frag = &shinfo->frags[i];
        frag_size = skb_frag_size(frag);
        if (offset >= frag_size) {
            offset -= frag_size;
            continue;
        }
        if (frag_size >= offset + len)
            return skb_frag_address(frag) + offset;
    }

    if (skb_copy_bits(skb, (int)frag_offset, buf, (int)len))
        return NULL;

    return buf;
}

int DATARMNET9303cec796(struct sk_buff*skb)
{
    int is_flow_controllable = 0;
    struct iphdr*ip4h, ip4_buf;
    struct ipv6hdr*ip6h, ip6_buf;

    switch (skb->protocol) {
    case htons(ETH_P_IP):
        ip4h = DATARMNETefcaf5fbe9(skb, 0, sizeof(*ip4h), &ip4_buf);
        if (!ip4h) break;
        if (!ip_is_fragment(ip4h) && (ip4h->protocol == IPPROTO_TCP || ip4h->protocol == IPPROTO_UDP)) {
            is_flow_controllable = 1;
            break;
        }
        if (ip4h->protocol == IPPROTO_ICMP) {
            skb->hash = 0;
            skb->sw_hash = 1;
        }
        break;
    case htons(ETH_P_IPV6):
        ip6h = DATARMNETefcaf5fbe9(skb, 0, sizeof(*ip6h), &ip6_buf);
        if (!ip6h) break;
        if (!(ip6h->nexthdr == NEXTHDR_FRAGMENT) && (ip6h->nexthdr == IPPROTO_TCP || ip6h->nexthdr == IPPROTO_UDP)) {
            is_flow_controllable = 1;
            break;
        }
        if (ip6h->nexthdr == NEXTHDR_ICMP) {
            skb->hash = 0;
            skb->sw_hash = 1;
        }
        break;
    default:
        break;
    }
    DATARMNETda96251102(DATARMNETcd24fca747, DATARMNET116c96c236, is_flow_controllable, 0, 0, 0, skb, NULL);
    return is_flow_controllable;
}

// ... This is the start of the full function block you need ...
int DATARMNETe488c1c396(struct DATARMNET63d7680df2*DATARMNET63b1a086d5,u8 
DATARMNETd87669e323,u8 DATARMNET5447204733){int DATARMNET5c4a331b9c;u32 
DATARMNETd3673fd5f0;u32 DATARMNET9bbfe49633;int ret=(0xd2d+202-0xdf7);int 
DATARMNET5a2e9192f9=-(0xd26+209-0xdf6);int DATARMNET8ceb7a8cc9;int 
DATARMNET42a992465f;int DATARMNETcfb5dc7296;int DATARMNETeaf6716f3e;struct 
DATARMNETe600c5b727*DATARMNET373e474754;u8 map=DATARMNET63b1a086d5->
DATARMNETfbbec4c537;DATARMNET5c4a331b9c=DATARMNETb6bff4a724(DATARMNET63b1a086d5)
;do{DATARMNET5a2e9192f9=DATARMNET63b1a086d5->map_cpu;if(DATARMNET5c4a331b9c<
(0xd2d+202-0xdf7)){DATARMNET63b1a086d5->DATARMNET6250e93187=(0xd2d+202-0xdf7);
ret=(0xd26+209-0xdf6);break;}DATARMNET63b1a086d5->DATARMNET6250e93187=
(0xd26+209-0xdf6);if(!map){DATARMNET63b1a086d5->DATARMNET6250e93187=
(0xd2d+202-0xdf7);ret=(0xd26+209-0xdf6);break;}if(DATARMNET5c4a331b9c==
DATARMNET63b1a086d5->map_index){ret=(0xd26+209-0xdf6);break;}DATARMNETd3673fd5f0
=DATARMNETadb0248bd4(DATARMNET63b1a086d5->map_cpu);DATARMNET9bbfe49633=
DATARMNET63b1a086d5->queue_head;DATARMNET42a992465f=DATARMNET63b1a086d5->map_cpu
;DATARMNETeaf6716f3e=DATARMNET3de2536baf(DATARMNET42a992465f).qlen+
DATARMNET832731a933(DATARMNET42a992465f).qlen;if((DATARMNET63b1a086d5->
DATARMNET85c698ec34&&(!DATARMNETeaf6716f3e))||(!DATARMNET63b1a086d5->
DATARMNET85c698ec34&&DATARMNETd3673fd5f0>=DATARMNET9bbfe49633)||(
DATARMNETd87669e323)){if(likely(DATARMNETa7909611da)){if(DATARMNET63b1a086d5->
DATARMNET85c698ec34&&!((DATARMNET765b8ecfba(DATARMNET63b1a086d5->dev,
DATARMNET5c4a331b9c,DATARMNETd87669e323)==(0xd2d+202-0xdf7)))){ret=
(0xd26+209-0xdf6);break;}DATARMNETcfb5dc7296=DATARMNETaef946bb68(
DATARMNET5c4a331b9c,DATARMNET63b1a086d5->DATARMNETfbbec4c537);if(
DATARMNETcfb5dc7296<(0xd2d+202-0xdf7)){ret=(0xd26+209-0xdf6);break;}
DATARMNET0997c5650d[DATARMNETcfb5dc7296].DATARMNET4133fc9428+=
DATARMNET63b1a086d5->DATARMNETae4b27456e.DATARMNET6215127f48;DATARMNET0997c5650d
[DATARMNET63b1a086d5->map_cpu].DATARMNET4133fc9428-=DATARMNET63b1a086d5->
DATARMNETae4b27456e.DATARMNET6215127f48;DATARMNET63b1a086d5->map_index=
DATARMNET5c4a331b9c;DATARMNET63b1a086d5->map_cpu=DATARMNETcfb5dc7296;
DATARMNET8ceb7a8cc9=DATARMNET63b1a086d5->map_cpu;if(DATARMNETd3673fd5f0<
DATARMNET9bbfe49633){DATARMNETb7ddf3c5dd[DATARMNET28bb261646]++;
DATARMNETb7ddf3c5dd[DATARMNET67b67dc88f]+=(DATARMNET9bbfe49633-
DATARMNETd3673fd5f0);DATARMNET4bde88919f(DATARMNET42a992465f,DATARMNET9bbfe49633
-DATARMNETd3673fd5f0);}if(DATARMNET63b1a086d5->DATARMNET341ea38662)
DATARMNET63b1a086d5->DATARMNET341ea38662->DATARMNET6e1a4eaf09=
DATARMNET8ceb7a8cc9;if(DATARMNET0997c5650d[DATARMNET42a992465f].
DATARMNETef866573e0){DATARMNET0997c5650d[DATARMNET8ceb7a8cc9].
DATARMNET1e1f197118=(0xd26+209-0xdf6);DATARMNETb7ddf3c5dd[DATARMNETc3bce05be2]++
;}else{DATARMNETb7ddf3c5dd[DATARMNET14067f0be4]++;}DATARMNET373e474754=&
DATARMNET0997c5650d[DATARMNET63b1a086d5->map_cpu];DATARMNETe074a09496();
DATARMNET63b1a086d5->queue_head=DATARMNET373e474754->DATARMNETae196235f2;
DATARMNET63b1a086d5->queue_head+=DATARMNET63b1a086d5->DATARMNETae4b27456e.
DATARMNET6215127f48;DATARMNETe102b3a798(DATARMNET63b1a086d5,&DATARMNET373e474754
->DATARMNET3dc4262f53,DATARMNET42a992465f);DATARMNET52de1f3dc0(
DATARMNET4510abc30d,DATARMNET052f49b190,DATARMNET63b1a086d5->map_cpu,
DATARMNET5a2e9192f9,(0x16e8+787-0xc0c),(0x16e8+787-0xc0c),DATARMNET63b1a086d5,
NULL);}ret=(0xd26+209-0xdf6);}}while((0xd2d+202-0xdf7));DATARMNETda96251102(
DATARMNET4510abc30d,DATARMNET23b8465daf,ret,DATARMNET63b1a086d5->map_cpu,
DATARMNET5a2e9192f9,(0x16e8+787-0xc0c),DATARMNET63b1a086d5,NULL);return ret;}

void DATARMNETfbc06e60f1(u8 DATARMNET42a992465f){struct DATARMNET63d7680df2*
DATARMNET3f85732c70;struct list_head*DATARMNET7b34b7b5be,*next;unsigned long 
ht_flags;u32 DATARMNET61ab18a4bd;u32 DATARMNETed7800fc72=(0xd2d+202-0xdf7);u32 
DATARMNETa0df5de99d=(0xd2d+202-0xdf7);u32 DATARMNET8bf94cc2f7=(0xd2d+202-0xdf7);
u32 DATARMNET76192fa639=(0xd2d+202-0xdf7);DATARMNETe074a09496();
DATARMNET52de1f3dc0(DATARMNET4510abc30d,DATARMNETde91850c28,DATARMNETecc0627c70.
DATARMNETa2e32cdd3a,DATARMNETecc0627c70.DATARMNETc252a1f55d,(0x16e8+787-0xc0c),
(0x16e8+787-0xc0c),NULL,NULL);local_bh_disable();spin_lock_irqsave(&
DATARMNET3764d083f0,ht_flags);DATARMNET61ab18a4bd=DATARMNETeb3978575d(
DATARMNET42a992465f);list_for_each_safe(DATARMNET7b34b7b5be,next,&
DATARMNET0997c5650d[DATARMNET42a992465f].DATARMNET3dc4262f53){
DATARMNET3f85732c70=list_entry(DATARMNET7b34b7b5be,struct DATARMNET63d7680df2,
DATARMNET04c88b8191);if(DATARMNET3f85732c70->DATARMNETae4b27456e.
DATARMNET6215127f48){DATARMNETed7800fc72=DATARMNET3f85732c70->
DATARMNETae4b27456e.DATARMNET6215127f48;DATARMNETa0df5de99d=DATARMNET3f85732c70
->DATARMNETae4b27456e.DATARMNETbaa5765693;DATARMNETe02152c351(
DATARMNET3f85732c70,(0xd26+209-0xdf6),DATARMNET5b5927fd7e);DATARMNET8bf94cc2f7+=
DATARMNETed7800fc72;DATARMNET76192fa639+=DATARMNETa0df5de99d;if(
DATARMNET3f85732c70->map_cpu==DATARMNET42a992465f){DATARMNET61ab18a4bd+=
DATARMNETed7800fc72;DATARMNET3f85732c70->queue_head=DATARMNET61ab18a4bd;}}}
DATARMNETecc0627c70.DATARMNETc252a1f55d-=DATARMNET76192fa639;DATARMNETecc0627c70
.DATARMNETa2e32cdd3a-=DATARMNET8bf94cc2f7;DATARMNET0997c5650d[
DATARMNET42a992465f].DATARMNETef866573e0=(0xd2d+202-0xdf7);DATARMNETecc0627c70.
DATARMNET132b9c7dc4[DATARMNET42a992465f].DATARMNETe61d62310f=(0xd2d+202-0xdf7);
DATARMNET0997c5650d[DATARMNET42a992465f].DATARMNET4133fc9428=(0xd2d+202-0xdf7);
spin_unlock_irqrestore(&DATARMNET3764d083f0,ht_flags);local_bh_enable();
DATARMNET52de1f3dc0(DATARMNET4510abc30d,DATARMNET576793621a,DATARMNETecc0627c70.
DATARMNETa2e32cdd3a,DATARMNETecc0627c70.DATARMNETc252a1f55d,DATARMNET8bf94cc2f7,
DATARMNET76192fa639,NULL,NULL);}

// ... All other functions from your original file go here ...

/* The final init function, corrected */
void DATARMNET45d8cdb224(struct net_device*dev, struct net_device*vnd)
{
    int rc;
    u8 i;
    u8 map_mask = 0;
    u8 map_len = 0;

    if (DATARMNETecc0627c70.DATARMNETfc89d842ae)
        return;

#if LINUX_VERSION_CODE < KERNEL_VERSION(5, 4, 0)
    struct rps_map *map = rcu_dereference(vnd->_rx->rps_map);
    if (map) {
        map_mask = DATARMNET928c931df9(map);
        map_len = DATARMNET310c3eb16e(map_mask);
    }
#endif

    DATARMNETecc0627c70.port = rmnet_get_port(dev);
    DATARMNETecc0627c70.map_mask = map_mask;
    DATARMNETecc0627c70.map_len = map_len;
    DATARMNETecc0627c70.DATARMNETba3f7a11ef = 4;
    DATARMNETecc0627c70.DATARMNET5c24e1df05 = 1;
    DATARMNETecc0627c70.DATARMNET7d667e828e = 1;

    for (i = 0; i < DATARMNETc6782fed88; i++)
        INIT_LIST_HEAD(&DATARMNET0997c5650d[i].DATARMNET3dc4262f53);

    DATARMNETe6e8431304();
    rc = register_oom_notifier(&DATARMNET105c85d84c);
    if (rc < 0) {
        pr_info("Rmnet_shs_oom register failure");
    }
    pr_info("rmnet_shs init with %x", DATARMNETecc0627c70.map_mask);
    DATARMNETecc0627c70.DATARMNETfc89d842ae = 1;
}

/* The notifier function must be fully defined */
static int DATARMNET2aa4ef6ff9(struct notifier_block *nb, unsigned long event, void *ptr)
{
    int freed_count, skb_count, cpu;
    int *p_freed = (int*)ptr;
    struct sk_buff_head *process_queue;
    struct sk_buff_head *input_queue;

    for_each_possible_cpu(cpu) {
        process_queue = &DATARMNET3de2536baf(cpu);
        input_queue = &DATARMNET832731a933(cpu);
        freed_count = skb_queue_len(process_queue);
        skb_count = skb_queue_len(input_queue);

        if (DATARMNET1ad396a890 && (freed_count + skb_count) >= DATARMNET1ad396a890) {
            DATARMNET82e88dbb56(&per_cpu(softnet_data, cpu).input_pkt_queue, cpu);
            freed_count = skb_queue_len(process_queue);
            skb_count = skb_queue_len(input_queue);
            if (skb_count >= DATARMNET1ad396a890) {
                DATARMNET82e88dbb56(process_queue, cpu);
            }
            (*p_freed)++;
        }
    }
    return 0;
}
