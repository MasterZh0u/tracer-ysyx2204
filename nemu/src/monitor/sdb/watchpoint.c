/***************************************************************************************
* Copyright (c) 2014-2022 Zihao Yu, Nanjing University
*
* NEMU is licensed under Mulan PSL v2.
* You can use this software according to the terms and conditions of the Mulan PSL v2.
* You may obtain a copy of Mulan PSL v2 at:
*          http://license.coscl.org.cn/MulanPSL2
*
* THIS SOFTWARE IS PROVIDED ON AN "AS IS" BASIS, WITHOUT WARRANTIES OF ANY KIND,
* EITHER EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO NON-INFRINGEMENT,
* MERCHANTABILITY OR FIT FOR A PARTICULAR PURPOSE.
*
* See the Mulan PSL v2 for more details.
***************************************************************************************/

#include "sdb.h"

#define NR_WP 32

static WP wp_pool[NR_WP] = {};
static WP *head = NULL, *free_ = NULL;

void init_wp_pool() {
  int i;
  for (i = 0; i < NR_WP; i ++) {
    wp_pool[i].NO = i;
    wp_pool[i].next = (i == NR_WP - 1 ? NULL : &wp_pool[i + 1]);
  }

  head = NULL;
  free_ = wp_pool;
}
static int number = 1;
/* TODO: Implement the functionality of watchpoint */
WP* new_wp(char *condation, bool *success){
  if (free_->next == NULL){
    assert(0);
  }
  
  WP* result = free_->next;
  result->NO = number ++;
  free_->next = result->next;
  result->next = NULL;
  expr(condation, success);
  strcpy(result->condation, condation);
  
  if (head == NULL){
    head = result;
  }else{
    result->next = head->next;
    head->next = result;
  }

  return result;
}

static void insert_free(WP *wp){
  wp->next = free_->next;
  free_->next = wp;
}

void free_wp(int NO){
  if (head->NO == NO){
    WP* buffer = head->next;
    insert_free(head);
    head = buffer;
    return ;
  }

  WP* prev = head;
  while (prev->next){
    if (prev->next->NO == NO){
      WP* buffer = prev->next->next;
      insert_free(prev->next);
      prev->next = buffer;
      return ;
    }
    prev = prev->next;
  }

  printf("未找到 \e[1;36mWatchPoint(NO.%d)\e[0m\n", NO);
}

void watchpoint_display(){
  printf("NO.\tCondation\n");
  WP* cur = head;
  while (cur){
    printf("\e[1;36m%d\e[0m\t\e[0;32m%s\e[0m\n", cur->NO, cur->condation);
    cur = cur->next;
  }
}