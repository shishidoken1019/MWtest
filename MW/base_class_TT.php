<?php

// SimpleTest�Ѵ���ե�����

require_once '/opt/www/simpletest/unit_tester.php';
require_once '/opt/www/simpletest/reporter.php';

// �оݤˤʤ륯�饹��include
require_once('target_class.inc');

class simple_test_TT extends UnitTestCase
{
//
public function __construct()
{
  $this->UnitTestCase();
}

// 
public function test()
{
  $obj = new target_class;

  // �������ϥƥ���
  $this->assertIdentical($obj->method(), false);

  // ����ϡ�diff�äƶ��ʤ���ספä�������
  // ������ˡ�Ͻ���Ʊ�ʤΤǰ�����������
  $awk = �оݤˤʤ�����;
  $twk = array_diff($awk, array("value1-1", "value1-2", "value1-3"));
  $this->assertIdentical($twk, array());

  // NULL��
  $this->assertNull($obj->method());
  $this->assertNotNull($obj->method());

}
}

// ��Ư��ʬ���ѹ�����
$test = new simple_test_TT;
$test->run(new TextReporter());

