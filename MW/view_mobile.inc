<?php

/**
 * ������View���饹
 *
 * ��ʸ���Ѵ����줿
 *
 * @package magicweapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  yyyy/mm/dd
 * @version $Id$
 **/

require_once('emoji_convert.inc');
require_once('view.inc');
require_once('mobile_info.inc');

class view_mobile extends view {

//
public function __construct() { parent::__construct(); }

public function output_extra($s)
{
  // �ޤ���̽���
  $s = parent::output_extra($s);

  // ��ʸ���Ѵ�����
  if ($this->get_res_obj()->is_need_convert()) {
//print "Trap\n";
    $obj = new emoji_convert;
    $s = $obj->convert($s);
  }

  // XXX ��������Ūuid����
  $uid = "";
  if (isset($_POST['uid'])) {
      $uid = $_POST['uid'];
  } else
  if (isset($_GET['uid'])) {
    $uid = $_GET['uid'];
  }
  // PC�ǤΥǥХå� & Docomo��SSL ��
  $wk = $this->get_model_obj()->get_mobile();
  if ( (false === $wk->is_mobile()) ||
       ( (true === $wk->is_docomo()) && ((false === empty($_SERVER['HTTPS']))&&('off' !== $_SERVER['HTTPS'])) )
     ) {
    if ("" !== $uid) {
      $s = str_replace('NULLGWDOCOMO', $uid, $s);
      $s = str_replace('guid=on', 'uid=' . $uid, $s);
    }
  }
//var_dump($uid);

  //
  // NULLGWDOCOMO��������Ĥ������ʤ���
  // ����guid=on����
  // XXX ¿ʬ�����ϡ�docomo�ʤ�add�פΤ��ɤ�����������ɤͤ� orz
  $wk = $this->get_model_obj()->get_mobile();
  if (false === $wk->is_docomo()) {
    //$s = str_replace('?uid=NULLGWDOCOMO&', '?', $s);
    //$s = str_replace('?uid=NULLGWDOCOMO', '', $s);
    //$s = str_replace('&uid=NULLGWDOCOMO&', '&', $s);
    //$s = str_replace('&uid=NULLGWDOCOMO', '', $s);
    //$s = str_replace('?guid=on&', '?', $s);
    //$s = str_replace('?guid=on', '', $s);
    //$s = str_replace('&guid=on&', '&', $s);
    //$s = str_replace('&guid=on', '', $s);

    $s = str_replace(array('?uid=NULLGWDOCOMO&',
                           '?uid=NULLGWDOCOMO',
                           '&uid=NULLGWDOCOMO&',
                           '&uid=NULLGWDOCOMO',
                           '?guid=on&',
                           '?guid=on',
                           '&guid=on&',
                           '&guid=on' ) ,
                      array('?', '', '&', '', '?', '', '&', '' ) ,
                      $s);
  }

  //
  return $s;
}

/**
 * ���ꤵ�줿�ե�����̾�˴�Ť����ե�������ɤ߹����ʸ������֤�
 *
 * �빽ʣ���ʽ����򤷤Ƥ롣
 * ���Ȥꤢ����XMLͥ��
 * ����ü����ĥ�Ҥ�xtpl��tpl�˸��ꤷ�Ƥ�(���ľ���Ȼפ�����
 * ����ĥ�Ҥ�xtpl�ʤ�XML(XHTML)��Ƚ�ǡ��ե�������Ƭ��XML������ڤ��ؤ���
 * ����ĥ�Ҥ�xtpl�ǥ���ꥢ��docomo�ξ��إå����Ѥ���
 * ���ƥ�ץ졼�ȥǥ��쥯�ȥ��ֵ���̾��θ�פˤ���
 *   �������֤Ȥ��Ƥ�
 *   template_dir/�����ͭ̾/tfile.tpl
 *   template_dir/����ꥢ(i | s | e)/tfile.tpl
 *   template_dir/mobile/tfile.tpl
 *   template_dir/tfile.tpl
 *
 * @access public
 * @return string �ե����뤬����¸�ߤ��ʤ������㳰���ꤲ��
 */
public function get_template_string()
{
  // ɬ�פʥ��󥹥��󥹤���
  $mobj = $this->get_model_obj();
//var_dump($mobj);


  // �ޤ��ե��������
  // ��ǽ���Τ���ѥ���켰���߾夲��
  // XXX ¿ʬ���Ȥǥ᥽�åɳ�����

  // ɬ�פʥ��󥹥��󥹤���
  $mobj = $this->get_model_obj();
//var_dump($mobj);

  // �ƥ�ץ졼�ȥǥ��쥯�ȥꤲ��
  $tdir = $mobj->get_config()->find('template_dir');

  // �ե�����̾�����ĥ�Ҿʤ����Τ���
  if (!(false === strpos($mobj->get_tmp_filename(), '.tpl'))) {
    $base_tmp_fn =  $mobj->get_tmp_filename();
    $base_tmp_xfn =  substr($base_tmp_fn, 0, (strlen($base_tmp_fn)-3)) . 'xtpl';
  } else {
    $base_tmp_xfn =  $mobj->get_tmp_filename();
    $base_tmp_fn =  substr($base_tmp_xfn, 0, (strlen($base_tmp_xfn)-4)) . 'tpl';
  }
//var_dump($base_tmp_fn);
//var_dump($base_tmp_xfn);

  // mobile_info����
  $mobobj = $mobj->get_mobile();

  // �Ȥ�Ω��
  $guess_paths = array();

  // template_dir/�����ͭ̾/tfile.tpl
  $guess_paths[] = $tdir . '/' . $mobobj->get_type() . '/' . $base_tmp_xfn;
  $guess_paths[] = $tdir . '/' . $mobobj->get_type() . '/' . $base_tmp_fn;

  // template_dir/����ꥢ(i | s | e)/tfile.tpl
  if (true === $mobobj->is_ez()) {
    $c = 'e';
  } else
  if (true === $mobobj->is_softbank()) {
    $c = 's';
  } else {
    // �ǥե���ȤϤȤꤢ����docomo��
    $c = 'i';
  }
  $guess_paths[] = $tdir . '/' . $c . '/' . $base_tmp_xfn;
  $guess_paths[] = $tdir . '/' . $c . '/' . $base_tmp_fn;

  // template_dir/mobile/tfile.tpl
  $guess_paths[] = $tdir . '/mobile/' . $base_tmp_xfn;
  $guess_paths[] = $tdir . '/mobile/' . $base_tmp_fn;

  // template_dir/tfile.tpl
  $guess_paths[] = $tdir . '/' . $base_tmp_xfn;
  $guess_paths[] = $tdir . '/' . $base_tmp_fn;
//var_dump($guess_paths);

  // ʸ�������
  $flg = false;
  $template_file = "";

  // ¸�ߤ��Ƥ���ե������õ���Ф�
  foreach($guess_paths as $p) {
    if (true === is_file($p)) {
      $flg = true;
      $template_file = $p;
      break;
    }
  }
  // �ե����뤬¸�ߤ��ʤ���ФϤ���
  if (false === $flg) {
    throw new Exception("template file not find!!");
  }

  // �ե�����ʸ��������
  $ret = file_util::read_file($template_file);

  // XML�ʤ��
  if (!(false === strpos($template_file, '.xtpl'))) {
    // ��Ƭ��XML��������ä��������
    // <?xml
    $pt = '/[\r\n]*<\?xml(.*)?>[\r\n]*/';
    $ret = preg_replace($pt, '', $ret);
    // <!DOCTYPE
    $pt = '/[\r\n]*<!DOCTYPE(.*)?>[\r\n]*/';
    $ret = preg_replace($pt, '', $ret);
    // <html
    $pt = '/[\r\n]*<html(.*)?>[\r\n]*/';
    $ret = preg_replace($pt, '', $ret);

    // XML�������̤�add
    if ($mobobj->is_docomo()) {
      $wk = '<?xml version="1.0" encoding="Shift_JIS" ?>
<!DOCTYPE html PUBLIC "-//i-mode group (ja)//DTD XHTML i-XHTML(Locale/Ver.=ja/2.2) 1.0//EN" "i-xhtml_4ja_10.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ja">';
      // �Ĥ��Ǥ�header���ڤ��ؤ���
      $mobj->get_cgi_response()->set_content('application/xhtml+xml; charset=Shift_JIS');
    } else
    if ($mobobj->is_ez()) {
      $wk = '<?xml version="1.0" encoding="Shift_JIS" ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML Basic 1.0//EN" "http://www.w3.org/TR/xhtml-basic/xhtml-basic10.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ja">';
    } else
    if ($mobobj->is_softbank()) {
      $wk = '<?xml version="1.0" encoding="Shift_JIS" ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML Basic 1.0//EN" "http://www.w3.org/TR/xhtml-basic/xhtml-basic10.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ja">';
    } else {
      // PC�Ȥ���
      $wk = '<?xml version="1.0" encoding="Shift_JIS" ?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML Basic 1.0//EN" "http://www.w3.org/TR/xhtml-basic/xhtml-basic10.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="ja">';
    }
    // ������դ�­���Ƥ���
    $ret = $wk . $ret;
  }
//var_dump($ret);

  // XXX is_docomo�Ȥ�uri�Ȥ���������­���Ƥ���?
/*
  $uri_ = $this->get_model_obj()->get_config()->find("uri");
  $uri_ssl_ = $this->get_model_obj()->get_config()->find("uri_ssl");
  $mx_domain_ = $this->get_model_obj()->get_config()->find("mx_domain");
  $conv->monoDic("uri", $uri_);
  $conv->monoDic("uri_ssl", $uri_ssl_);
  $conv->monoDic('mx_domain', $mx_domain_);
*/

  //
  return $ret;
}

//private:

} // end of class
