<?php

/**
 * CGI �ꥯ�����ȥ��饹
 *
 * CGI�ꥯ�����Ȥ�EUC���������Ѵ������ͤ��֤�
 * ¾������ȥ��󥹥���ɬ�ܤ�����PHP�ǤϤ���ʤ�����
 * XXX �Хåե���󥰤ˤ����ǽ����ϸ����ޥ����äƴ�����
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('multibyte.inc');
require_once('file_util.inc');
require_once('guess_from_data_encoding.inc');
require_once('debug_util.inc');

//
class cgi_request {

//
public function __construct()
{
  $this->init();
}

//
public function init()
{
  // �ǥե���Ȥ򤳤��ˤ��Ƥ���
  $this->set_hi_priority_post();
  // XXX cgi_requestñ�ΤǻȤ���褦�˰������
  // XXX ���Ȥǥ��󥳡��ɥ������Ѥ�����褦�ˤ��롩
  $ieobj = new multibyte;
  $ieobj->set_euc();

  // in�ο�¬
  $gobj = new guess_from_data_encoding;
  // ��¬
  $gobj->guess();
  // ��¬������
  $ieobj->set_guess_from_string($gobj->get_encoding_string());
  //
  $this->set_inside_encoding_obj($ieobj);
}

/**
 * ��侩�ʤΤǵ��ˤ��ʤ��褦��
 */
public function set_priority($s) { $this->priority_ = $s; }
public function get_priority() { return $this->priority_; }

/**
 * Get��Post�⸫�˹Ԥ�����Post�����ͥ�褵����
 * @access    public
 */
public function set_hi_priority_post() { $this->priority_ = "pg"; }

/**
 * Get��Post�⸫�˹Ԥ�����Get�����ͥ�褵����
 * @access    public
 */
public function set_hi_priority_get() { $this->priority_ = "gp"; }

/**
 * Get�Τߤ򸫤˹Ԥ�
 * @access    public
 */
public function set_only_get() { $this->priority_ = "g"; }

/**
 * Post�Τߤ򸫤˹Ԥ�
 * @access    public
 */
public function set_only_post() { $this->priority_ = "p"; }

/**
 * ʸ��������·���ѥ��饹����
 * 
 */
public function set_inside_encoding_obj($o)
  { $this->inside_encoding_obj_ = $o; }
protected function get_inside_encoding_obj()
  { return $this->inside_encoding_obj_; }

/**
 *
 * ������̾��������Post��Get
 *
 */
public function get_all_names()
{
  $p_key = array_keys($_POST);
  $g_key = array_keys($_GET);
  // �����­������
  $ret =  array_unique(array_merge($p_key, $g_key));
  //
  return $ret;
}


/**
 * �������β�������[���� | ñ�ѿ�]����������ꤹ��
 * XXX ����ä�UTIL�Ԥ��ʤΤ���
 * @access    protected
 * @param     &array	$base	�ͤ��������٤�����
 * @param     array	$add	­����������
 */
protected function _add_array(&$base, $add)
{
  if (is_array($add)) {
    foreach ($add as $wk) {
      array_push($base, $wk);
    }
  } else {
    array_push($base, $add);
  }
}

/**
 * �������ؿ���Get��������
 * @access    public
 * @param     string	$key	�����Ѥ�key��name=value��name��ʬ������
 * @return    array�ޤ���string	���(������)���ͤ�̵������null���֤�
 */
public function _get_get($key) {
  if (isset($_GET[$key])) {
    return $_GET[$key];
  }
  return null;
}

/**
 * �������ؿ���Post��������
 * @access    public
 * @param     string    $key    �����Ѥ�key��name=value��name��ʬ������
 * @return    array�ޤ���string ���(������)���ͤ�̵������null���֤�
 */
public function _get_post($key) {
  if (isset($_POST[$key])) {
    return $_POST[$key];
  }
  return null;
}

/*
 * ���ꤵ�줿������¸�ߥ����å�
 */
public function is_exist($key)
{
  // �������꤬�ʤ�����ͤ��֤�
  if ("" == $key) {
    return false;
  }

  // Ƚ�곫��
  $flg = false;
  $length = strlen($this->priority_);
  for($i = 0; $i < $length; $i ++) {
    $itr = $this->priority_[$i];
    // p�ʤ�post��������
    if ("p" == $itr) {
      $wk = $this->_get_post($key);
    }
    // g�ʤ�get��������
    if ("g" == $itr) {
      $wk = $this->_get_get($key);
    }
    // �ǡ��������ä���true��
    if (!(is_null($wk))) {
      $flg = true;
    }
  }

  //
  return $flg;
}

/**
 * Get�⤷����Post�������򸡺�����̤�����ˤ����֤�
 * XXX �ǡ���������ʸ�������ɤ�EUC��ľ���Ƥ����֤�
 * @access    public
 * @param     string	$key	�����Ѥ�key��name=value��name��ʬ������
 * @return    array(string)	��̤����󡣤ʤ����϶�������֤�
 */
public function find_array($key = "")
{
$ret = array();
  // �������꤬�ʤ�����ͤ��֤�
  if ("" == $key) {
    return $ret;
  }

  // Ƚ��
  $length = strlen($this->priority_);
  for($i = 0; $i < $length; $i ++) {
    $itr = $this->priority_[$i];
    // p�ʤ�post��������
    if ("p" == $itr) {
      $wk = $this->_get_post($key);
    }
    // g�ʤ�get��������
    if ("g" == $itr) {
      $wk = $this->_get_get($key);
    }
    // �ǡ��������ä��äݤ��ʤ�
    if (!(is_null($wk))) {
//debug_util::dump_string_put($wk);
      // ­������
      $this->_add_array($ret, $wk);
    }
  }

  // ʸ���������ִ�
  $eret = array();
  foreach ($ret as $buf) {
//debug_util::dump_string_put($buf);
    // XXX magic_quote�к��ɲ�
    if (1 === get_magic_quotes_gpc()) {
//print "magic_quote<br>\n";
      $buf = stripslashes($buf);
    }
//print "befor buf $buf<br>";
//debug_util::dump_string_put($buf);

    // ��ʸ�������ѳƼ�
    $buf = $this->interruption_emoji($buf);
//print "befor buf $buf<br>";
//debug_util::dump_string_put($buf);
    if (false === is_null($this->get_inside_encoding_obj())) {
      $buf = $this->get_inside_encoding_obj()->convert($buf);
    }
//debug_util::dump_string_put($buf);
//print "\n";
//var_dump($buf);
    array_push($eret, $buf);
  }

  //
  return $eret;
}

// ñ���ѥ�åѡ�
/**
 * Get�⤷����Post�������򸡺�����̤�ñ�ͤ��֤�
 * @access    public
 * @param     string	$key	�����Ѥ�key��name=value��name��ʬ������
 * @return    string	��̡��ʤ����Ϥ���ʸ�����֤�
 */
public function find($key = "")
{
  $ret = $this->find_array($key);
  if (0 == count($ret)) {
    return "";
  }
  //
  return $ret[0];
}

/**
 * Cookie�������򸡺�����̤�����ˤ����֤�
 *
 * XXX �Ȥꤢ����ʸ���������ִ��Ϥ����ʤ�
 *
 * @access    public
 * @param     string	$key	�����Ѥ�key��name=value��name��ʬ������
 * @return    array(string)	��̤����󡣤ʤ����϶�������֤�
 */
public function find_cookie_array($key = "")
{
	$ret = array();

  // �������꤬�ʤ�����ͤ��֤�
  if ("" == $key) {
    return $ret;
  }

  // �ǡ�����̵������ͤ��֤�
  if (!(isset($_COOKIE[$key]))) {
    return "";
  }
  // �ǡ�������
  $wk = $_COOKIE[$key];

  // ����ǤϤʤ�(ñ��)�ξ��
  if (!(is_array($wk))) {
    // �����
    $ret = array($wk);
  } else {
    // ���Τޤ��
    $ret = $wk;
  }

  // magic_quote��off�ʤ�
  if (0 === get_magic_quotes_gpc()) {
    return $ret;
  }

  // on�ʤ�
  $ret2 = array();
  foreach ($ret as $buf) {
    // XXX magic_quote�к��ɲ�
    $ret2[] = stripslashes($buf);
  }

  //
  return $ret2;
}


// ñ���ѥ�åѡ�
/**
 * Cookie�������򸡺�����̤��֤�
 * @access    public
 * @param     string    $key    �����Ѥ�key��name=value��name��ʬ������
 * @return    string    ��̡��ʤ����Ϥ���ʸ�����֤�
 */
public function find_cookie($key = "")
{
  $ret = $this->find_cookie_array($key);
  if (0 == count($ret)) {
    return "";
  }
  //
  return $ret[0];
}

/*
XXX ��롩
get_path_info()
*/

/**
 * �����̤�ʣ�������褬����Ȥ���Ƚ�Ǥ��ȯ��
 * XXX type="image"��̤��θ
 *
 * �Ȥ�¦�Υ��᡼���Ȥ��Ƥ�
 * // �ǥե���Ȥ������top
 * $btn_name_array = ('rss_list_button', 'rss_result_button');
 * $btn_name = $req->choice($btn_name_array);
 * 
 * // �ǥե���Ȥ�����Ū�˻���
 * $btn_name_array = ('rss_list_button', 'rss_result_button');
 * $btn_name = $req->choice($btn_name_array, 'no_choice');
 *
 * @access    public
 * @param     array     $names  �����å��оݤ�name����
 * @param     string    $default �оݤ����٤�NG���ä����Υǥե����
 * @return    array(string)     ��̤����󡣤ʤ����϶�������֤�
 */
public function choice($names, $default = "")
{
  // �ǥե�������ꡣ�ʤ����ϡ��������Ƭ�פ�����
  $ret = $default;
  if ("" == $ret) {
    $ret = $names[0];
  }

  // �����å�
  foreach ($names as $name) {
    // ���Ĥ��ä���
    if ("" != $this->find($name)) {
      // ���ꤷ��ȴ���Ф�
      $ret = $name;
      break;
    }
  }
  //
  return $ret;
}

/**
 * upload�ե�����μ���
 *
 * @access public
 * @param string $name FORM�ǻ��ꤷ��name
 * @param boolean $encode_flg true�ʤ�ʸ��code��encode���롣default��false
 * @return string �ե��������ȡ����顼�ξ���ʸ����
 */
public function get_file($name, $encode_flg = false)
{
  // ��������å�
  if (false === is_uploaded_file($_FILES[$name]['tmp_name'])) {
    return "";
  }
  // XXX move_uploaded_file �Ϥ��ʤ���tmp�ξ�����Ȥ����ݤ���
  // XXX ���Ȥ����ӡ�get_file_to_file�פȤ��Ĥ��뤫��

  // ��Ȥ�Ȥ����
  $s = file_util::read_file($_FILES[$name]['tmp_name']);  

  // �⤷encodeɬ�פʤ餹��
  if (true === $encode_flg) {
    $s = $this->get_inside_encoding_obj()->convert($s);
  }

  //
  return $s;
}

/**
 * ��ʸ���ѤΥݥ��ե������ѥ��ߡ��᥽�å�
 *
 * @access public
 * @param string $s �ǡ���
 * @return string ����
 */
public function interruption_emoji($s)
{
  //
  return $s;
}


//private:
private $priority_;
private $inside_encoding_obj_;  // �������󥳡����� multibyte���󥹥���

} // end of class
