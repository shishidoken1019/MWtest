<?php

// SimpleTest�Ѵ���ե�����

require_once '/opt/www/simpletest/unit_tester.php';
require_once '/opt/www/simpletest/reporter.php';

// �оݤˤʤ륯�饹��include
require_once('mw_config.inc');

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
  $obj = new mw_config;

  // �ޤ��ե����������
  $obj->set_file('mw_config.conf');

  // 0 �����ȥѥ�����Ƽ�
  $this->assertNull( $obj->find('command_ng1') );
  $this->assertNull( $obj->find('command_ng2') );
  $this->assertNull( $obj->find('command_ng3') );


  // 1 nomal �ѥ�����
  // command = includefile.inc:classname
  $robj = $obj->find('command');
  $this->assertNotNull($robj);
  $this->assertIdentical($robj->get_include_filename(), 'include.inc');
  $this->assertIdentical($robj->get_classname(), 'class');
  $this->assertIdentical($robj->get_template_filename(), '');
  $this->assertIdentical($robj->get_error_template_filename(), '');
  $this->assertIdentical($robj->get_ssl_type(), '');

  // ��άɽ��
  // command = :
  $robj = $obj->find('command_abbreviation');
  $this->assertNotNull($robj);
  $this->assertIdentical($robj->get_include_filename(), 'command_abbreviation.inc');
  $this->assertIdentical($robj->get_classname(), 'command_abbreviation');
  $this->assertIdentical($robj->get_template_filename(), '');
  $this->assertIdentical($robj->get_error_template_filename(), '');
  $this->assertIdentical($robj->get_ssl_type(), '');

  // ��άɽ����
  // command = dir/:
  $robj = $obj->find('command_abbreviation2');
  $this->assertNotNull($robj);
  $this->assertIdentical($robj->get_include_filename(), 'dir/command_abbreviation2.inc');
  $this->assertIdentical($robj->get_classname(), 'command_abbreviation2');
  $this->assertIdentical($robj->get_template_filename(), '');
  $this->assertIdentical($robj->get_error_template_filename(), '');
  $this->assertIdentical($robj->get_ssl_type(), '');

  // �ɲ�
  // command = includefile.inc:classname template_filename,
  $robj = $obj->find('command_add1');
  $this->assertNotNull($robj);
  $this->assertIdentical($robj->get_include_filename(), 'include.inc');
  $this->assertIdentical($robj->get_classname(), 'class');
  $this->assertIdentical($robj->get_template_filename(), 'template.tpl');
  $this->assertIdentical($robj->get_error_template_filename(), '');
  $this->assertIdentical($robj->get_ssl_type(), '');

  // command = includefile.inc:classname template_filename,erro_temp.tpl
  $robj = $obj->find('command_add2');
  $this->assertNotNull($robj);
  $this->assertIdentical($robj->get_include_filename(), 'include2.inc');
  $this->assertIdentical($robj->get_classname(), 'class2');
  $this->assertIdentical($robj->get_template_filename(), 'template2.tpl');
  $this->assertIdentical($robj->get_error_template_filename(), 'error_template.tpl');
  $this->assertIdentical($robj->get_ssl_type(), '');

  // command = includefile.inc:classname ,erro_temp.tpl
  $robj = $obj->find('command_add3');
  $this->assertNotNull($robj);
  $this->assertIdentical($robj->get_include_filename(), 'include3.inc');
  $this->assertIdentical($robj->get_classname(), 'class3');
  $this->assertIdentical($robj->get_template_filename(), '');
  $this->assertIdentical($robj->get_error_template_filename(), 'error_template3.tpl');
  $this->assertIdentical($robj->get_ssl_type(), '');

  // command = includefile.inc:classname template_filename,erro_temp.tpl
  $robj = $obj->find('command_add4');
  $this->assertNotNull($robj);
  $this->assertIdentical($robj->get_include_filename(), 'include4.inc');
  $this->assertIdentical($robj->get_classname(), 'class4');
  $this->assertIdentical($robj->get_template_filename(), 'template4.tpl');
  $this->assertIdentical($robj->get_error_template_filename(), 'error_template4.tpl');
  $this->assertIdentical($robj->get_ssl_type(), 'ssl');


  // �ɲá���άɽ��
  //command = dir/: input.tpl ssl
  $robj = $obj->find('command_composite');
  $this->assertNotNull($robj);
  $this->assertIdentical($robj->get_include_filename(), 'dirc/command_composite.inc');
  $this->assertIdentical($robj->get_classname(), 'command_composite');
  $this->assertIdentical($robj->get_template_filename(), 'composite.tpl');
  $this->assertIdentical($robj->get_error_template_filename(), '');
  $this->assertIdentical($robj->get_ssl_type(), 'ssl');

  // ����ʣ����
  $robj = $obj->find('command_ex1');
  $this->assertNotNull($robj);
  $this->assertIdentical($robj->get_include_filename(), 'include4.inc');
  $this->assertIdentical($robj->get_classname(), 'class4');
  $this->assertIdentical($robj->get_template_filename(), 'template4.tpl');
  $this->assertIdentical($robj->get_error_template_filename(), 'error_template4.tpl');
  $this->assertIdentical($robj->get_ssl_type(), 'ssl');


  //
  return true;
}
}

// ��Ư��ʬ���ѹ�����
$test = new simple_test_TT;
$test->run(new TextReporter());

