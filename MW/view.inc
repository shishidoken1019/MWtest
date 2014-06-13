<?php

/**
 * View���饹
 *
 * ����Ū�ˤϽ��Ϥ��ƽ����
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('file_util.inc');

class view {

//
public function __construct() { $this->init(); }

//
public function init() { }

public function set_body($s) { $this->body_ = $s; }
// XXX
public function get_body() {
 if ("" != $this->body_) {
   return $this->body_;
  }
  // else
  return $this->get_body_from_convert();
}

public function set_res_obj($o) { $this->res_obj_ = $o; }
public function get_res_obj() { return $this->res_obj_; }

public function set_multi_obj($o) { $this->multi_obj_ = $o; }
public function get_multi_obj() { return $this->multi_obj_; }

public function set_model_obj($o) { $this->model_obj_ = $o; }
public function get_model_obj() { return $this->model_obj_; }

public function get_template_string()
{
  //
  $tf = $this->get_template_filename();
  return file_util::read_file($tf);
}

public function get_template_filename()
{
  // ɬ�פʥ��󥹥��󥹤���
  $mobj = $this->get_model_obj();
//var_dump($mobj);

  // �ƥ�ץ졼�ȥե������full�ǥ��쥯�ȥ����
//var_dump($mobj);
//var_dump($mobj->get_tmp_filename());
//var_dump($tf);
  $tf = $mobj->get_config()->find('template_dir') . $mobj->get_tmp_filename();

  // �ե����뤬¸�ߤ��ʤ���ФϤ���
  if (false === is_file($tf)) {
    throw new Exception("template file not find!!");
  }

  //
  return $tf;
}


// body�����ΤȤ���model���餴�ꤴ�����
// ���顼�ʤ��ʸ��
public function get_body_from_convert()
{
//print "get_body_from_convert \n";
  // ɬ�פʥ��󥹥��󥹤���
  $mobj = $this->get_model_obj();
  $incode = $mobj->get_inside_encoding_obj();
  // XXX ��̯���ݤ��ʤ�������
  $incode->set_from_encoding_unknown();
  // conv���󥹥��󥹤���
  // ��conv�����ɤ�ʤ�󤫤ͤ�
  $conv = $mobj->get_conv();

  $cn = get_class($conv);
  if (false === (stristr($cn, 'smarty'))) {
    // �ƥ�ץ졼�ȥե������ʸ����Ȥ��Ƽ���
    $ts = $this->get_template_string();
    //
    $out = $conv->conv($incode->convert($ts));
  } else {
    // �ƥ�ץ졼�ȥե�����̾�����
    $fn = $this->get_template_filename();
    // smartyŪ����
    $out = $conv->fetch($fn);
  }

  //
  return $out;
}

//
public function put_contents_header()
{
  //
  $res = $this->get_res_obj();
//var_dump($res);
  // �إå��ν���
  $res->set_nocache();
  $res->put();
}

public function get_contents_body()
{
  //
  $res = $this->get_res_obj();
  $mobj = $this->get_multi_obj();

  // body�ν���
  if ($res->is_need_convert()) {
    // ʸ���Ϥäݤ��Τ��ִ����ƽ��ϡ�
    return $mobj->convert( $this->get_body() );
  }
  // else
  // ʸ���������ִ�ɬ�פʤ������ʤΤǤ��Τޤޡ�
  return $this->get_body();
}

//
public function output()
{
  // �ޤ�����
  //print $this->get_contents_body();
  $out = $this->get_contents_body();
  if ("" === $out) {
    throw new Exception("body is empty!!");
  }
  //
  $out = $this->output_extra($out);

  // �إå�����
  $this->put_contents_header();

  // body����
  // echo���ᤤ�Ȥ������äʤΤǡĤޤ����
  //print $out;
  echo $out;

  //
  return true;
}

// ����ľ���Ǥν������ִ��Ȥ���������ä���
// ���̤ʽ����򤹤�Ȥ��Ϥ����˾�񤤤�
public function output_extra($s) {
  return $s;
}


//private:
private $body_;
private $res_obj_;
private $multi_obj_;
private $model_obj_; // XXX �������ꡩ

} // end of class
