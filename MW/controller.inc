<?php
/**
 * ����ȥ����饯�饹
 *
 * MVC�ˤ�����C��ô�����륯�饹
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 **/

require_once('cgi_request.inc');
require_once('cgi_response.inc');
require_once('load_manager.inc');
require_once('multibyte.inc');
require_once('security.inc');
require_once('multimap.inc');
require_once('guess_from_data_encoding.inc');
require_once('mw_config.inc');
require_once('mobile_info.inc');
require_once('user_agent_check.inc');
require_once('config_extension.inc');

class controller {

//public:
// config���󥹥��󥹤Υ�������
protected function set_config_obj($o) { $this->cfobj_ = $o; }
public function get_config_obj() { return $this->cfobj_; }

//
protected function set_cgi_request_obj($o) { $this->reqobj_ = $o; }
public function get_cgi_request_obj() { return $this->reqobj_; }
//
protected function set_cgi_response_obj($o) { $this->resobj_ = $o; }
public function get_cgi_response_obj() { return $this->resobj_; }
//
protected function set_bag_obj($o) { $this->bag_ = $o; }
public function get_bag_obj() { return $this->bag_; }

//
protected function set_mobile_obj($o) { $this->mobobj_ = $o; }
public function get_mobile_obj() { return $this->mobobj_; }
//
protected function set_inside_encoding_obj($o)
  { $this->inside_encoding_obj_ = $o; }
public function get_inside_encoding_obj()
  { return $this->inside_encoding_obj_; }

//
protected function set_output_encoding_obj($o)
  { $this->output_encoding_obj_ = $o; }
public function get_output_encoding_obj()
  { return $this->output_encoding_obj_; }


public function __construct()
{
  // �Хåե���󥰳���
  //ob_clean(); // XXX ���顼�������������ǽ��������Τǰ�ü�����ȥ�����
  ob_start();

  //
  $this->init();
}

/**
 * ���������
 *
 * @access public
 */
public function init()
{
  $this->set_config_obj(new config_extension);
  $this->set_mobile_obj(new mobile_info);
}

/**
 * ���󥹥�������
 *
 * request & response ��Ϥ���Ȥ��Ƥ��ޤ��ޤʥ��󥹥��󥹤�����
 * bag��multibyte�Ϥʤ�
 *
 * @access public
 * @return boolean �������ä���false
 */
public function make_instancees()
{
  // �󥤥󥹥�������
  // XXX ��������ʤ���ľ��
  $this->set_bag_obj( new multimap );

  // �������󥳡����ѥ��饹����
  // in��Ǥ�ա�out��config����
  // �ǥե���Ȥ�EUC
  $ieobj = new multibyte;
  // out������
  $ieobj->set_euc();
  if ($wk = $this->get_config_obj()->find('inside_encoding_type')) {
    $ieobj->set_guess_to_string($wk);
  }
  // in�ο�¬
  $gobj = new guess_from_data_encoding;
  if ("" !== $this->get_config_obj()->find('encoding_hinting_name')) {
    $gobj->set_encoding_string($this->get_config_obj()->find('encoding_hinting_name'));
  }
  // ��¬
  $gobj->guess();
  // ��¬������
  $ieobj->set_guess_from_string($gobj->get_encoding_string());
//var_dump($ieobj);
//print "inside " . $ieobj->get_charset_string() . "\n";
  //
  $this->set_inside_encoding_obj($ieobj);

  // ���ϥ��󥳡����ѥ��饹����
  // in�ϡ��������󥳡��ɤ�out ��out��config����
  // �ǥե���Ȥ�EUC
  $opobj = new multibyte;
  // out������
  $opobj->set_sjis();
  if ($wk = $this->get_config_obj()->find('output_encoding_type')) {
    $opobj->set_guess_to_string($wk);
  }
  // in������
  if ($wk = $this->get_config_obj()->find('inside_encoding_type')) {
    $opobj->set_guess_from_string($wk);
  }
//print "output " . $opobj->get_charset_string() . "\n";
  $this->set_output_encoding_obj($opobj);

  // CGI REQUEST���󥹥��󥹤�����
  $req = $this->get_instance('cgi_request', 'cgi_request.inc:cgi_request');

  // �����Post Get�׽�Ȥ���
  // XXX ��ǥ���ե����ǤϤ�����
  $req->set_hi_priority_post();
  $req->set_inside_encoding_obj($this->get_inside_encoding_obj());
  //
  $this->set_cgi_request_obj($req);

  // CGI RESPONSE���󥹥��󥹤�����
  $res = new cgi_response;
  //
  $this->set_cgi_response_obj($res);

  //
  return true;
}

/**
 * config�ե���������
 *
 * config�ե�����̾�����ꡧ���θ�ɬ�פʽ��������餻��
 *
 * @access public
 * @param string $fn config�ե�����̾
 * @return boolean �������ä���false
 */
public function set_config($fn)
{
  // �ޤ���local�ʥ���ե����������
  $this->get_config_obj()->set_file($fn);
//var_dump($this->get_config_obj());

  ////////////////////////////////
  // ����ե������������Ƽ�
  ////////////////////////////////

  // common_include_dir�β��äƤ�����set_ini
  foreach ($this->get_config_obj()->find_array('common_include_dir') as $path) {
    set_include_path(get_include_path() . PATH_SEPARATOR . $path);
//print $path . "\n";
//print get_include_path() . "<BR>\n";
  }
  //
  return true;
}

/**
 * ����������å�
 *
 * �������������������᥽�å�
 * ��user-agent-arrow �ޤ��� user-agent-denny �����ꤵ��Ƥ���е�������å�
 *
 *
 *
 * @access public
 * @return boolean ���꤬�����false
 */
public function entrance_check()
{
$ret = true;

  // ����Ƚ��
  // XXX ξ�����ꤵ��Ƥ��륱�����ϤȤꤢ����̤��θ
  $afn = $this->get_config_obj()->find('user-agent-arrow');
  $dfn = $this->get_config_obj()->find('user-agent-denny');
//var_dump($afn);
//var_dump($dfn);
  if ( ("" !== $afn) || ("" !== $dfn) ) {
    $obj = new user_agent_check;
    $obj->set_mobile_obj($this->get_mobile_obj());
    $fn = "";
    if ("" !== $afn) {
      $fn = $afn;
      $obj->set_arrow_string(file_get_contents($fn));
    } else {
      $fn = $dfn;
      $obj->set_denny_string(file_get_contents($fn));
    }
//var_dump($fn);

    // Ƚ��
    $ret = $obj->is_permission();

    // XXX ���������ԲĤʻ��ν���
    if (false === $ret) {
      $uri = $this->get_config_obj()->find('user-agent-disapprove_uri');
      if ('' !== $uri) {
        // XXX �����ȥ٥�
        header('Location:' . $uri);
        exit;
      }
      // else
      // XXX �Ĥ���⤫�ʤ�٥� orz
      echo 'your user-agent is denny.';
      exit;
    }
  }
//var_dump($ret);

  //
  return $ret;
}

/**
 * �и������å�
 *
 * ����������θ������᥽�å�
 * �Ѿ����ɬ�פʤ�������Ƥ�������
 *
 * @access public
 * @return boolean ���꤬�����false
 */
public function exit_check() { return true; }

/**
 * ���ϥǡ����ѡ���&�ǥ�����
 *
 * PHPŪ�ˤϤ�뤳�Ȥʤ��ʤ�
 *
 * @access public
 * @return boolean ���꤬�����false
 */
public function parse_decode() 
{
  //
  return true;
}

/**
 * Model���������ʬ�ᥤ��
 *
 * @access public
 * @param string $cstring ���ޥ��̾
 * @param int $recursive_counter �Ƶ��ѥ�����
 * @return base_model_inc base_model�ϥ��󥹥���
 */
public function run_main($cstring, $recursive_counter)
{
//print "run_main c = $cstring\n";
//var_dump($this->mapdata_);
//var_dump($recursive_counter);
//exit;

  // �����쥯�Ȥˡְ�ʸ���ᥢ������������פ�cstring�ƤӽФ����Ȥ�NG
  if ( (0 === $recursive_counter)&&('_' === $cstring[0]) ) {
    throw new Exception("\"" . $cstring . "\" is invalid command(2)!!");
  }

  // õ���Ƥߤ롣̵����Х��顼���ͤ��֤�
  if (is_null($model_data = $this->mapdata_->find($cstring))) {
    throw new Exception("\"" . $cstring . "\" is invalid command!!");
  }
//var_dump($model_data);
//print "include is " . $model_data->get_include_filename() . "<BR>\n";
//print "class is " . $model_data->get_classname() . "<BR>\n";

  // include����
  // XXX load_file�Υ롼�������model�Υ��顼���ФƤ��ʤ���
  require_once($model_data->get_include_filename());
/*
  if (false === load_manager::load_file($include_filename)) {
    //throw new Exception("\"" . $include_filename . "\" is invalid !!");
    throw new Exception("$cstring model class file is invalid !!");
  }
*/

  // ���֥������Ⱥ���
  $classname =  $model_data->get_classname();
  $model_ins = new $classname;

  // ɬ�פʾ��������
  // XXX ����Ū��referer�Ϥ��ʤΤǾ���϶�ͭ�Ǥ���Ϥ�
  $model_ins->set_config($this->get_config_obj());
  $model_ins->set_cgi_request($this->get_cgi_request_obj());
  $model_ins->set_cgi_response($this->get_cgi_response_obj());
  $model_ins->set_inside_encoding_obj($this->get_inside_encoding_obj());
  $model_ins->set_my_name($cstring);
  $model_ins->set_bag_obj($this->get_bag_obj());
  $model_ins->set_mobile($this->get_mobile_obj());
//print "\nbag \n";
//var_dump($this->get_bag_obj());

  // map�ե���������꤬���äƤ��Ĥ��줬��񤭤���Ƥʤ������ꤹ���
//print "Trap 1\n";
//var_dump($model_data->get_template_filename());
//var_dump($model_ins->is_tmp_filename());
  if (("" !== $model_data->get_template_filename())&&(false === $model_ins->is_tmp_filename())) {
//print "Trap 2\n";
    $model_ins->set_tmp_filename($model_data->get_template_filename());
  }
  if (("" !== $model_data->get_error_template_filename())&&(false === $model_ins->is_error_tmp_filename())) {
//print "Trap 3\n";
    $model_ins->set_error_tmp_filename($model_data->get_error_template_filename());
  }

  // ���󥹥��󥹤˥��å�
  $model_ins->initialize();
  if ($model_ins->is_recursive_on()) {
    // �Ƶ�Ū�ɤ߹��ߤäݤ��Τǡ�����³��call
    $m_ins = $this->run_main($model_ins->get_recursive_command(), $recursive_counter + 1);
  } else {
    $model_ins->execute(); // ������Body������Ƥ�ĤϤ�!!
    if ($model_ins->is_recursive_on()) {
      // �Ƶ�Ū�ɤ߹��ߤäݤ��Τǡ�����³��call
      $m_ins = $this->run_main($model_ins->get_recursive_command(), $recursive_counter + 1);
      // ��äƤ����ͤ򲣼�ꤷ����������
      // XXX base64�Ȥ�������������դ䤵��Ȥʤ�
      $model_ins->set_body($m_ins->get_body());
    }
  }
  // ��λ����
  $model_ins->finalize();
//var_dump($model_ins);

  // �ǡ�����
  //return $model_ins->get_body();
  // XXX ���󥹥��󥹤��Τ�Τ����������롣���base64�Ȥ��ǤƤ��뤫��
//print "\nbag \n";
//var_dump($this->get_bag_obj());
  return $model_ins;
}


/**
 * �ᥤ�����
 *
 * ɬ�פʽ�����ɬ�פʽ��֤�call����
 *
 * @access public
 */
public function run()
{
  // �㳰������ª����
  try {
    // ���󥹥�������
    if (!($this->make_instancees())) {
      throw new Exception("make re instance error!!");
    }

    // ����������å�
    if (!($this->entrance_check())) {
      throw new Exception("entrance ceck error!!");
    }

    // ���ϥǡ����ѡ���&�ǥ�����
    if (!($this->parse_decode())) {
      throw new Exception("parse or decode ceck error!!");
    }

    // �ޥåԥ�
    // �ޥåԥ󥰥ե�����μ���
    $map_file = $this->get_config_obj()->find('mapping_file_path');
//print $map_file . "\n";

    // �ޥåԥ󥰥ե�����β���
    //$this->mapdata_ = new config;
    //$this->mapdata_->set_file($map_file);
    $this->mapdata_ = new mw_config;
    $this->mapdata_->set_file($map_file);

    // Controller �ᥤ��
    // �����å�ʸ����μ���
    // XXX c����Ѥˤ����ۤ���������������ʤ���
    $cstring = $this->get_cgi_request_obj()->find("c");

    if ("" == $cstring) {
      // XXX �ɤ����롩 ���index��ĥ�뤱��
      $cstring = "index";
    }

    // ���ꤵ�줿model��á��
    // XXX return�͡�string�Ǥ����Τ�������
    // XXX �褯�ʤ����饤�󥹥��󥹤��Ȥ��Ƥߤ�
//print "cstring is $cstring \n";
    $model_obj = $this->run_main($cstring, 0);

    // View����
    $vobj = $this->get_instance('view_class', 'view.inc:view');
    $vobj->set_body($model_obj->get_body());
    $vobj->set_res_obj($this->get_cgi_response_obj());
    $vobj->set_multi_obj($this->get_output_encoding_obj());
    $vobj->set_model_obj($model_obj);
    $vobj->output();

    // XXX �����Ǥ褤����
    ob_end_flush();

  } catch (Exception $e) {
// XXX
  print "get exception!!!\n";
  print security::sanitize_html($e->getMessage()) . "\n";
//print $e->getCode() . "\n";
//print $e->getFile() . "\n";
//print $e->getLine() . "\n";
//print_r($e->getTrace());
//print $e->getTraceAsString() . "\n";
  }

  // �����Ȥ��ν�λ����
  // XXX try����ˤ���롩
  $this->exit_check();
}

protected function get_instance($name, $default)
{
  // View����
  $v = $this->get_config_obj()->find($name);
  if ("" === $v) {
    $v = $default;
  }

  //
  $awk = explode(":", $v);
  $inc = trim($awk[0]);
  $class = trim($awk[1]);

  //
  require_once($inc);
  $obj = new $class;

  //
  return $obj;
}


//private:
private $cfobj_;	// �����ȸ�ͭ��config��config���饹���󥹥���
private $mobobj_;	// mobile_info���饹�Υ��󥹥���
private $reqobj_;	// CGI REQUEST ���󥹥���
private $resobj_;	// CGI RESPONSE ���󥹥���
private $mapdata_;	// �ޥåԥ󥰥ե������ѡ�config���󥹥���
private $inside_encoding_obj_;	// �������󥳡����� multibyte���󥹥���
private $output_encoding_obj_;	// ������ multibyte���󥹥���
private $bag_obj_;	// model��������ѳ󥤥󥹥���


} // end of class
