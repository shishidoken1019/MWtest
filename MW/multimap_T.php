<?php
require_once('multimap.inc');

$obj = new multimap;

  // �ǡ������ͤù���
  $obj->insert('test-name1', 'test-value1-1');
  $obj->insert('test-name1', 'test-value1-2');
  $obj->insert('test-name1', 'test-value1-3');
  $obj->insert('test-name2', 'test-value2-1');
  $obj->insert('test-name2', 'test-value2-2');
  $obj->insert('test-name3', 'test-value3-1');
  $obj->insert('test', 'test-value');

  // ���� ���ƥ졼���Ǥ֤�ޤ路
  $names = array();
  $values = array();
  for($itr = $obj->begin(); $itr != $obj->end(); $itr ++) {
    // ʸ�������
    $names[] = $obj->real($itr)->get_first();
    $values[] = $obj->real($itr)->get_second();
  }
//var_dump($names);
//var_dump($values);

  // key����
  $values = $obj->find_array('test-name1');
//var_dump($values);

  // ñ��
  $s = $obj->find('test', 'test-value');


