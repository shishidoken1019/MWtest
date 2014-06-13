<?php

/**
 * �Х�ǡ��� util
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('validator_clump_unit.inc');

class validator_util {

public function __construct()
{
  //
  $this->init();
}

//
public function init()
{
  $this->set_cgi_name_prefix("");
  $this->set_cgi_name_sufix("");
  $this->set_cgi_req(null);
  $this->set_validator_list(array());

  //
  $this->clump_ = array();
  $this->error_val_ = array();

  // XXX ���ܸ�ɽ���Ǥ��ˤ礴�ˤ�
  $this->clear_type_string();
  //
  $this->push_type_string("alphanum", "�ѿ���");
  $this->push_type_string("numeric", "����");
  $this->push_type_string("digit", "����");
  $this->push_type_string("email", "email");
  $this->push_type_string("url", "URL");
  $this->push_type_string("dir", "�ǥ��쥯�ȥ�̾���Ѳ�ǽʸ��");
  $this->push_type_string("date", "����");
}

// �������å�
public function set_cgi_req($o) { $this->req_ = $o; }
public function get_cgi_req() { return $this->req_; }

public function set_validator_list($a) { $this->validators_ = $a; }
public function get_validator_list() { return $this->validators_; }

//
public function set_cgi_name_prefix($s) { $this->cgi_name_prefix_ = $s; }
public function get_cgi_name_prefix() { return $this->cgi_name_prefix_; }
public function set_cgi_name_sufix($s) { $this->cgi_name_sufix_ = $s; }
public function get_cgi_name_sufix() { return $this->cgi_name_sufix_; }

// XXX ��ǥ��顼���̤Ȥ�����뤫��
protected function set_error($n, $nn) { $this->error_val_[$n][$nn] = 1; }
public function get_error() { return $this->error_val_; }

/*
public function push_clump($n, $o, $a = array()) {
  if ("" === $n) { return false; }
  $this->clump_obj_[$n] = $o;
  $this->clump_list_[$n] = $a;
}
*/
// XXX �ǡ����λ�������̯��
public function push_clump($n, $o, $a = array()) {
  if ("" === $n) { return false; }
  $this->clump_[$n]['obj'] = $o;
  $this->clump_[$n]['list'] = $a;
}
protected function get_clump() { return $this->clump_; }

//
public function push_type_string($n, $v) { $this->type_string_[$n] = $v; }
public function get_type_string($n) {
	// XXX 2007/06/28 yamada 
	// notice���Ф�Τ���¸�ߥ����å��ɲ�
	if (isset($this->type_string_[$n])) {
		return $this->type_string_[$n];
	}
	return "";
}

public function clear_type_string() { $this->type_string_ = array(); }

// �����ᥤ��
// bool check()
// ��ĤǤ�NG�������false�ͤ��֤�
// XXX ���̸ߴ��ѡ����ȤǾä��Ȼפ�¿ʬ
// XXX ɬ�פ����Ǥ�get_validator_list��get_cgi_req
public function check()
{
  //
  $lists = $this->get_validator_list();
  $ret = true;
  $req = $this->get_cgi_req();

  // �֤��
  foreach($lists as $list) {
//print_r($list);

    // �ޤ���̾���μ��Ф�
    // XXX
// XXXXXXXX
    $cgi_name = $this->get_cgi_name_prefix() . 
                $list->get_cgi_name() .
                $this->get_cgi_name_sufix();
//print "cgi $cgi_name \n";

    // �����å�
    if (false == $list->check($req->find($cgi_name))) {
      $ret = false;
    }
  }
  //
  return $ret;
}

/*
 * clump����ˤ��������������å�
 *
 * @return boolean �������꤬�����false
 **/
public function is_valid()
{
  // ���ʤ�İ�̣Ū�ˤ�true����ͤ�
  $clumps = $this->get_clump();
  if (empty($clumps)) {
    return true;
  }

  // req���ȤäȤ�
  $req = $this->get_cgi_req();

  // ����ޤ路��
$ret = true;
  foreach($clumps as $clump_name => $clump) {
    // �ޤ��оݤ�ʤ�
    $list = $clump['list'];
    if (empty($list)) {
      $list = $clump['obj']->get_all_names();
    }

    //
    $validators = $clump['obj']->get_validate_obj($list);

    // validator���󥹥��󥹤ҤȤĤŤĥ����å�
    foreach($validators as $name => $vobj) {
//var_dump($name);
//print "<br>\n";
//var_dump($vobj);

      //
      $cgi_name = $vobj->get_cgi_name($name);
//var_dump($cgi_name);

      // XXX ���Ȥ�isnull�Ϥ����ʤ���̵�̤���ͤ�
      if (is_null($req)) {
        $value = $clump['obj']->get_value($name);
      } else {
        $value = $req->find($cgi_name);
      }
//var_dump($value);
//print "<br>\n";
      // �ޤ����ߤ��ͤ���̤�����
      //$this->value_set_as_a_template_[$cgi_name] = $value;

      // validate
      // NG�ʤ�false�ˤ��Ȥ�
      if (false === $vobj->check($value)) {
//var_dump($name);
//var_dump($cgi_name);
//var_dump($value);
        $ret = false;
        // clump_name��name�����ꤷ�Ƥ���
        $this->set_error($clump_name, $name);

        // conv�֤������Ѿܺ�
        $wk = "if_error_" . $cgi_name;
        $this->value_set_as_a_template_[$wk] = true;

        // ɬ�ܥ����å�
        $wk = "if_error_must_" . $cgi_name;
        $this->value_set_as_a_template_[$wk] = ($vobj->is_error_must()) ? true : false;

        // type�����å�
        $wk = "if_error_type_" . $cgi_name;
        $wk2 = "valid_type_" . $cgi_name;
        $this->value_set_as_a_template_[$wk] = ($vobj->is_error_type()) ? true : false;
        $this->value_set_as_a_template_[$wk2] = $this->get_type_string($vobj->get_type());

        // min�����å�
        $wk = "if_error_min_" . $cgi_name;
        $wk2 = "valid_min_" . $cgi_name;
        $this->value_set_as_a_template_[$wk] = ($vobj->is_error_min()) ? true : false;
        $this->value_set_as_a_template_[$wk2] = $vobj->get_min();

        // max�����å�
        $wk = "if_error_max_" . $cgi_name;
        $wk2 = "valid_max_" . $cgi_name;
        $this->value_set_as_a_template_[$wk] = ($vobj->is_error_max()) ? true : false;
        $this->value_set_as_a_template_[$wk2] = $vobj->get_max();

      }
    }
  }
//var_dump($this->value_set_as_a_template_);

  //
  return $ret;
}

// XXX �ѻ�ͽ��
public function make_all_datas()
{
  //
  $lists = $this->get_validator_list();
  $req = $this->get_cgi_req();

  //
  $values = array();

  // 
  foreach($lists as $list) {
    //
    $name = $list->get_cgi_name();
    $cgi_name = $this->get_cgi_name_prefix() .
                $list->get_cgi_name() .
                $this->get_cgi_name_sufix();

    // �ޤ����ߤ��ͤ���̤�����
    $values[$name] = $req->find($cgi_name);
//print "$name -> $cgi_name \n";
  
    // ���顼������
    if (true == $list->is_error()) {
      //
      $wk = "if_error_" . $name;
      $values[$wk] = true;

      // ɬ�ܥ����å�
      $wk = "if_error_must_" . $name;
      $values[$wk] = ($list->is_error_must()) ? true : false;

      // type�����å�
      $wk = "if_error_type_" . $name;
      $wk2 = "valid_type_" . $name;
      $values[$wk] = ($list->is_error_type()) ? true : false;
      $values[$wk2] = $this->get_type_string($list->get_type());

      // min�����å�
      $wk = "if_error_min_" . $name;
      $wk2 = "valid_min_" . $name;
      $values[$wk] = ($list->is_error_min()) ? true : false;
      $values[$wk2] = $list->get_min();

      // max�����å�
      $wk = "if_error_max_" . $name;
      $wk2 = "valid_max_" . $name;
      $values[$wk] = ($list->is_error_max()) ? true : false;
      $values[$wk2] = $list->get_max();
    }
  }

  //
  return $values;
}

// XXX
public function get_value_set_as_a_template() { return $this->value_set_as_a_template_; }

//private:
private $req_;		// cgi_request���󥹥���
private $validators_;	// validator_clump_util������
//private $clump_obj_;	// clump�ϥ��󥹥��󥹳�Ǽ
//private $clump_list_;	// �о�list��all�ʤ������
private $clump_;	// ['obj']=���󥹥���  ['list']=list

//
private $error_val_;

// XXX ̾������̯���ʤ���
private $value_set_as_a_template_;

//
private $cgi_name_prefix_;
private $cgi_name_sufix_;
private $type_string_;	// type�����ܸ��ɽ��

} // end of class
