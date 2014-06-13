<?php

/**
 * �ǡ����β�(clump)���饹
 *
 * �ºݤˤϡ��ǡ�����Ǥޤ�ǰ���������
 * ��cgi���󥿥ե������ȤΤ����
 * ���ƥ�ݥ��ơ��֥�ȤΤ����
 * ��DB�ȤΤ����
 * �����礹�롣
 *
 * @package magicweapon
 * @link http://www.grid-works-guild.net/MagicWeapon/ MagicWeapon
 * @access  public
 * @author  Michiaki Wuzawa <wuzawa@m-fr.net>
 * @create  $LastChangedDate$
 * @version $Revision$
 */

require_once('basis_clump.inc');
require_once('tokenizer.inc');
require_once('calendar_util.inc');
require_once('security.inc');
require_once('sql_util.inc');
require_once('session_data_db.inc');
require_once('conv_util.inc');

class data_clump extends basis_clump
{
//public:

//
public function __construct()
{
  parent::__construct();
  //$this->init();
}

// �����
public function init()
{
  //
  parent::init();

  //
  $this->tblname_ = "";         // ����DB�ơ��֥�̾
  $this->dbh_ = null;           // DB�ϥ�ɥ�
  //
  $this->tmpname_ = "";         // �ƥ�ݥ��ơ��֥�̾
  $this->tmp_key_ = "";         // �ƥ�ݥ��ơ��֥��ѥ���

  //
  $this->nokeyname_ = array();  // Key�ǤϤʤ�̾���켰
  $this->keyname_ = array();    // Key�ˤʤäƤ�̾���켰

  //
  $this->cgi_name_ = array();   // CGI���̾��
  $this->tmp_name_ = array();   // �ƥ�ݥ��ơ��֥���̾��
  $this->db_name_ = array();    // ����DB���̾��
}


/**
 * DB�ơ��֥�̾������
 *
 * @access public
 * @param string $s �ơ��֥�̾
 */
public function set_table_name($s) { $this->tblname_ = $s; }
/**
 * DB�ơ��֥�̾�μ���
 *
 * @access public
 * @return string �ơ��֥�̾
 */
public function get_table_name() { return $this->tblname_; }


/**
 * �ƥ�ݥ��ơ��֥�̾������
 *
 * �ǡ�������Ū�˳�Ǽ���뤿��Τ��
 *
 * @access public
 * @param string $s �ơ��֥�̾
 */
public function set_session_table_name($s) { $this->tmpname_ = $s; }
/**
 * �ƥ�ݥ��ơ��֥�̾�μ���
 *
 * @access public
 * @return string �ơ��֥�̾
 */
public function get_session_table_name() { return $this->tmpname_; }



/**
 * DB�ϥ�ɥ������
 *
 * @access public
 * @param db_handle $o db_handle���饹(������������饹)�Υ��󥹥���
 */
public function set_db($o) { $this->dbh_ = $o; }
/**
 * DB�ϥ�ɥ������
 *
 * @access public
 * @return db_handle db_handle���饹(������������饹)�Υ��󥹥���
 */
public function get_db() { return $this->dbh_; }

// public����̯�ʤΤǤ��ȥ����ȤϽ񤫤ʤ�
public function set_tmp_key($s) { $this->tmp_key_ = $s; }
public function get_tmp_key() { return $this->tmp_key_; }
// key��ȡ����ʥ����Ǻ�������
public function make_tmp_key() { $this->set_tmp_key(tokenizer::get()); }

// XXX �ʲ���public������protected�äݤ��Τǥ����Ȥ����񤫤ʤ��ɤ�

// db�Ǥ�����̾�Υ�������
public function set_db_name($n, $v) { $this->db_name_[$n] = $v; }
public function get_db_name($n) { return $this->db_name_[$n]; }
// �ƥ�ݥ��ơ��֥�Ǥ�����̾�Υ�������
public function set_tmp_name($n, $v) { $this->tmp_name_[$n] = $v; }
public function get_tmp_name($n) { return $this->tmp_name_[$n]; }
// cgi form̾�Υ�������
public function set_cgi_name($n, $v) { $this->cgi_name_[$n] = $v; }
public function get_cgi_name($n) { return $this->cgi_name_[$n]; }
// keyname��Ϣ
public function push_keyname($n) { $this->keyname_[] = $n; }
public function get_all_key_names()   { return $this->keyname_; }

public function push_nokeyname($n) { $this->nokeyname_[] = $n; }
public function get_all_no_key_names() { return $this->nokeyname_; }


/**
 * �ǡ������å�
 *
 * �ǡ������ѹ���flg�λؼ��ˤ�äƤ�DB�ѹ���Ϣư������
 * XXX �祭�����Ф����ư��̤����
 *
 * @access public
 * @param string $name ̾��
 * @param string $value ���ꤹ����
 * @param boolean $flg �ѹ��ѥե饰��true��DB�ι�����Ԥ����ǥե���Ȥ�true
 * @return boolean ���꤬�����false
 */
public function set_value($name, $value, $flg = true)
{
//print "$name , $value ; \n";
  // ¸�ߥ����å�
  if( !($this->is_name($name)) ) {
    return false;
  }

  // �ǡ���������
  $this->set_data($name, $value);

  // flg�� true �ξ���DB�⹹��
  if ($flg) {
    $wk = $this->get_db_name($name) . "=" . security::sanitize_db_add_quote($value);
    //
    return $this->_mono_set_db($wk);
  }

  // flg �� false �ʤ顢DB�򹹿������˽�λ
  return true;
}

/**
 * �ǡ������å�
 *
 * �ǡ����������¸�ߤ��ʤ�����ʸ����
 * �ǡ����Ȥ��Ƥζ�ʸ���ʤΤ�¸�ߤ��ʤ��Τ������פʾ���is_name�Ȥä�
 *
 * @access public
 * @param string $name ̾��
 * @return string �͡��ǡ������ʤ���ж�ʸ��
 */
public function get_value($name)
{
  // XXX ¸�ߥ����å���get_data�᥽�åɤ˰�¸
  return $this->get_data($name);
}

/**
 * ���Ǥ�����
 *
 * data�켰���ꡣ
 * key_flg�ϡ�key|pk|k|ok|true|on �Τ����줫��key�Ǥ���Ȥߤʤ�
 * XXX ���public�����ɡ��������ꤹ��Τ��礤�Ȥ����ͤ���
 *
 * @access public
 * @param string $inname �����ƾ��Ѥ�̾��
 * @param string $cginame CGI Form�Ǥ�̾��
 * @param string $tmpname �ƥ�ݥ��ơ��֥��Ǥ�̾��
 * @param string $dbname DB��Ǥ�̾��
 * @param string $keyflg PK�ξ�硢������pk�ˤ���
 * @return boolean �������꤬�����false
 */
public function push_element
($inname, $cginame = "", $tmpname = "", $dbname = "", $keyflg = "")
{

  // ����Ǥ�inname�Ϥ��뤳�ȡ��ʤ���NG
  if( !isset($inname)) {
    return false;
  }
  if( "" === $inname) {
    return false;
  }

  // ��Ť�call���Ƥ��ʤ��������å�
  // XXX ��񤭤��ʤ���̵�뤹��
  if (true === $this->is_name($inname)) {
    return true;
  }

  // �ޤ�name����Ͽ
  parent::push_element($inname);

  // CGI̾�Τ�����
  if ("" === $cginame) {
    $cginame = $inname;
  }
  $this->set_cgi_name($inname, $cginame);

  // �ƥ�ݥ��ơ��֥�̾�Τ�����
  if ("" === $tmpname) {
    $tmpname = $inname;
  }
  $this->set_tmp_name($inname, $tmpname);

  // ����DB̾�Τ�����
  if ("" === $dbname) {
    $dbname = $inname;
  }
  $this->set_db_name($inname, $dbname);

  // key��Ƚ��
  if(preg_match("/^(key|pk|k|ok|true|on)$/i", $keyflg)) {
    $this->push_keyname($inname);
  } else {
    $this->push_nokeyname($inname);
  }
  //
  return true;
}

/**
 * �����å��᥽�å�
 *
 * �ǡ������ΤΥ����å���Ԥ����ޤ�validator
 * ���Υ��饹���Τ�Virtual��٥�β��������塹�˸������ѤʤΤǡ�
 *
 * @access public
 * @return boolean ���true
 */
public function check() { return true; }

/**
 * CGI����ξ���εۤ����
 *
 * DB�ؤμ�ư��Ǽ�ϹԤ�ʤ�!!
 *
 * @access public
 * @param cgi_request $req cgi_request���饹�Υ��󥹥���
 * @param boolean $empty_overwrite_flg ��ʸ���ξ�񤭥ե饰 true�ˤ���ȶ��ʤ��ʸ�����񤭤���
 * @return boolean �������꤬�����false
 */
public function set_from_cgi($req, $empty_overwrite_flg = false)
{
  // ���ǡ��������
  foreach($this->get_all_names() as $name) {
    // �����(�Ȥꤢ������)��Ǽ
    $wk = $req->find($this->get_cgi_name($name));
    // ��񤭥ե饰�� false ��
    if (false === $empty_overwrite_flg) {
      if ("" === $wk) {
        continue;
      }
    }
    //
    $this->set_value($name, $wk, false);
//print "$name <= $wk <br />\n";
  }

//print "set_from_cgi <BR>\n";
//print_r($this->data_);
//print "<BR>\n";

  return true;
}

//
protected function _make_session_instance()
{
  // ���֥����������������ܥǡ���������
  $se = new session_data_db;
  $se->init();
  $se->set_db($this->get_db());
  $se->set_id($this->get_tmp_key());
  if ("" !== $this->get_session_table_name()) {
    $se->set_tablename($this->get_session_table_name());
  }

  //
  return $se;
}

/**
 * �ƥ�ݥ��ơ��֥�ؤΥǡ����γ�Ǽ
 *
 * @access public
 * @param session_data_obj $se ���å����data���饹��null�ʤ鿷���˺��
 * @return boolean �������꤬�����false
 */
public function set_to_tmp($se = null)
{
  if (true === is_null($se)) {
    // ���������å�
    if("" === $this->get_tmp_key()) {
      // ���������ꤵ��Ƥʤ���к��
      // XXX ���顼�Τۤ����褤��������
      $this->make_tmp_key();
    }

    // ���֥����������������ܥǡ���������
    $se = $this->_make_session_instance();
  }

  // ���߾�����ɤ߹���
  $se->read();

  // ���֥������Ȥ����ǡ������ͤù���
  foreach($this->get_all_names() as $name){
    // ��Ǽ
    $se->add_once($this->get_tmp_name($name), $this->get_value($name));
  }

  // �񤭹���
  return $se->write();
}


/**
 * �ƥ�ݥ��ơ��֥뤫���������ĥ��
 *
 * tmp_key�����꤬�ʤ�����NG�ˤʤ�Τ�����
 *
 * @access public
 * @param session_data_obj $se ���å����data���饹��null�ʤ鿷���˺��
 * @return boolean �������꤬�����false
 */
public function set_from_tmp($se = null)
{
  
  if (true === is_null($se)) {
    // ���������å�
    if("" === $this->get_tmp_key()) {
      return false;
    }

    // ���֥����������������ܥǡ���������
    $se = $this->_make_session_instance();
  }

  // ���ǡ����μ���
  if(!($se->read())) {
    return false;
  }

  // ���֥������Ȥ����ǡ������ͤù���
  foreach($this->get_all_names() as $name) {
    // ��Ǽ
    $wk = $se->find($this->get_tmp_name($name));
    $this->set_value($name, $wk, false);
  }

  //
  return true;
}

/**
 * ����DB�ؤ���Ͽ�ؤΥ�åѡ�
 *
 * ���֤�set_to_db
 *
 * @access public
 * @return boolean �������꤬�����false
 */
public function set() { $this->set_to_db(); }

/**
 * ����DB�ؤ���Ͽ
 *
 * @access public
 * @return boolean �������꤬�����false
 */
public function set_to_db()
{
//print "into set <br />\n";
  // ���ܤ�insert
  if (!($this->insert())) {
//print "insert error <br />\n";
    // ���顼�ʤ�Update
    if (!($this->update())) {
//print "update error <br />\n";
      return false;
    }
  }
//print "fin set <br />\n";
  //
  return true;
}

// where������
// where�����hash�Ǻ�äƤ�
protected function _make_where()
{
  $where = array();
  foreach($this->get_all_key_names() as $name) {
    $where[ $this->get_db_name($name) ] = $this->get_data($name);
  }
  //
  return $where;
}

/**
 * �ǡ�����insert
 *
 * �����Τ�insert����
 * DB�ϥ�ɥ�̤����ξ��֤����ơ�PHP���顼�Ф��褦�ˤ��Ƥ�
 *
 * @access public
 * @param boolean $del_flg ��������ü�ե饰���ռ����ʤ�����!!
 * @return boolean �������꤬�����false
 */
public function insert($del_flg = false)
{
  // ���ǡ����γ�Ǽ
  $value = array();
  foreach($this->get_all_names() as $name) {
    $value[ $this->get_db_name($name) ] = $this->get_data($name);
  }
  // XXX
  if (true === $del_flg) {
    // �ǡ������ɲ�
    $value['delete_date'] = calendar_util::get_now_string();
    // SQL��ȯ��
    $sql = sql_util::make_insert($this->get_table_name() . '_delete', $value);
  } else {
    // SQL��ȯ��
    $sql = sql_util::make_insert($this->get_table_name(), $value);
  }

  //
  return $this->_sql($sql);
}

/**
 * �ǡ�����update
 *
 * �����Τ�update����
 * DB�ϥ�ɥ�̤����ξ��֤����ơ�PHP���顼�Ф��褦�ˤ��Ƥ�
 *
 * @access public
 * @return boolean �������꤬�����false
 */
public function update()
{
  // where��ʬ������
  $where = $this->_make_where();

  // value��ʬ������
  $value = array();
  foreach($this->get_all_no_key_names() as $name) {
    $value[ $this->get_db_name($name) ] = $this->get_data($name);
  }

  // SQL��ȯ��
  $sql = sql_util::make_update($this->get_table_name(), $value, $where);

  //
  return $this->_sql($sql);
}


/**
 * �ǡ�����delete
 *
 * �����Τ�delete����
 * DB�ϥ�ɥ�̤����ξ��֤����ơ�PHP���顼�Ф��褦�ˤ��Ƥ�
 * �ơ��֥�̾_delete�Ȥ����ơ��֥뤬�����硢������򤽤ä���insert
 *
 * @access public
 * @return boolean �������꤬�����false
 */
public function del()
{
  // where��ʬ������
  $where = $this->_make_where();

  // ����ơ��֥��insert
  // XXX �ե饰��������Ĥ��ʤ��� ����insert�����äƤ�̵�롢���٤ʤΤ���
  $this->insert(true);

  // SQL��ȯ��
  $sql = sql_util::make_delete($this->get_table_name(), $where);
  //
  return $this->_sql(sql_util::make_delete($this->get_table_name(), $where));
}

/**
 * �ǡ������Ĥ�update
 *
 * ����ޤ껶ȯŪ�ˤ���DB����٤����뤫�����դ��Ƥ�
 *
 * @access public
 * @param string $sql_p sql�Υѡ��ġ�����Ū�ˤ�set���Ϥ�SQLʸ���Τ��
 * @return boolean �������꤬�����false
 */
public function _mono_set_db($sql_p)
{
  //
  $where = $this->_make_where();

  // XXX ��������
  $sql = "UPDATE " . $this->get_table_name() . " SET " . $sql_p . " WHERE " . sql_util::make_where($where) . ";";
//print $sql . "\n";

  //
  return $this->_sql($sql);
}

/*
 * SQLȯ��
 *
 * XXX SELECT�ǤϻȤ��ʤ����Ȥ�����!!
 * public�ˤϤ��Ȥ����ɴ���protected����ͤ�
 *
 */
public function _sql($sql)
{
//print $sql . "\n";

  //
  $ret = $this->get_db()->query($sql);
//var_dump($ret);
  if (is_null($ret)) {
    return false;
  }
  if (false === $ret) {
    return false;
  }

  return true;
}

/**
 * �������Τμ���
 *
 * �����ʤ���key���ꤷ�ʤ���NG�ˤʤ�ޤ���
 *
 * @access public
 * @return boolean �������꤬�����false
 */
public function get()
{
  // where��ʬ�κ���
  $where = $this->_make_where();
  //
  return $this->_get($where);
}

/**
 * pk�ˤ��ʤ��������Τμ���
 *
 * pk�ǤϤʤ��ָ������ꤵ��Ƥ����͡פ���where���Ĥम�ޤ�
 *
 * @access public
 * @return boolean �������꤬�����false
 */
public function get_nopk()
{
  //
  $cols = $this->get_all_names();

  // �ͤ������Τ�and��where�Ȥ���
  $where = array();
  foreach ($cols as $col) {
    //
    if ("" !== $this->get_value($col)) {
      $where[$col] = $this->get_value($col);
    }
  }
  //
  return $this->_get($where);
}

/**
 * �������Τμ�������
 *
 * �����ʤ���key���ꤷ�ʤ���NG�ˤʤ�ޤ���
 * XXX key����pk�פ�����ͤ����ꤵ��Ƥ����Ρפ��ѹ��ˤʤ�ޤ���
 *
 * @access public
 * @param array &$where select���˻Ȥ�where������Ѥ�hash����
 * @return boolean �������꤬�����false
 */
public function _get(array &$where)
{
  // SELECT �����κ���
  $col = implode(",", $this->get_all_names());

  // SQL�κ���
  $sql = "SELECT " . $col . " FROM " . $this->get_table_name() . " WHERE " . sql_util::make_where($where) . ";";
//print $sql . "\n";

  // SQL��ȯ��
//print "---------------------\n";
//var_dump($this->get_db());
//print "---------------------\n";
  $res = $this->get_db()->query($sql);
//print $sql . "\n";
//var_dump($res);
  if (is_null($res)) {
    return false;
  }
  if (false === $res) {
    return false;
  }
  // �ǡ������ʤ����NG
  if (false === $res->fetch()) {
    return false;
  }
//print "<br />Trap1 <br />\n";
  $count = 0;
  $all_names = $this->get_all_names();
//print_r($all_names);
//print "<br />\n";

  foreach($all_names as $name) {
//print "Trap2 <br />\n";
    // �ǡ����򥤥󥹥�������ݻ�
    $this->set_value($name, $res->get_data($count), false);
//print "$name is " . $res->get_data($count) . "\n";

    //
    $count ++;
  }

  //
  return true;
}

/**
 * �����ϥå�������ˤ��Ƽ���
 *
 * @access public
 * @return map �ϥå�������
 */
public function get_all_data_to_hash()
{
  $ret = array();
  // �ޤ��Ϥ��٤Ƥι���̾�򤲤�
  $all_names = $this->get_all_names();

  // �ǡ�����
  foreach($all_names as $name) {
    $ret[$name] = $this->get_value($name);
  }
  //
  return $ret;
}

/**
 * monoDic�ǥǡ����켰�����ꤹ��
 *
 * XXX ʿ�����������ϥ᥽�å�
 * XXX get_all_data_to_hash�Υǡ�������ˤ��Ƥߤ롧���������Ѿ����˳�
 *
 * @access public
 * @param conv���󥹥��� $conv �ִ����󥸥󥤥󥹥���
 */
public function set_all_to_conv($conv)
{
  // ���饹̾����
  $cn = get_class($conv);
//var_dump($cn);

  foreach($this->get_all_data_to_hash() as $name => $value) {
    // ñ�ִ���
    if ('f_conv' === $cn) {
      $conv->monoDic($name, security::sanitize_html($value));
    } else
    if ('secure_conv' === $cn) {
      $conv->monoDic($name, $value);
    }
    // XXX else �Ĥɤ����롩
    // XXX ���smarty�����Ǥ�����뤫�����
  }

  //
  return true;
}


/**
 * ���ꤵ�줿�����˸������դ�����
 *
 * ���ν����ˤ����Ƽ�ưȿ�ǥե饰���ǥե�true�ʤΤ��ѤʤΤ�
 * �ǥե���false�ˤ��Ƥ���
 *
 * @access public
 * @param string $name �������դ����ꤷ���������̾
 */
public function set_value_nowdate($name, $flg = false)
{
  return $this->set_value($name, calendar_util::get_now_string(), $flg);
}


/**
 * ���ꤵ�줿�����˥ȡ���������
 *
 * ���ν����ˤ����Ƽ�ưȿ�ǥե饰���ǥե�true�ʤΤ��ѤʤΤ�
 * �ǥե���false�ˤ��Ƥ���
 * �ȡ�����̾��get_value�Ǥ��Ȥäơ�
 *
 * @access public
 * @param string $name �ȡ���������ꤷ���������̾
 */
public function set_value_token($name, $flg = false)
{
  return $this->set_value($name, tokenizer::get(), $flg);
}

/**
 * set_all_to_conv���줿conv���󥹥��󥹤��������
 *
 * secure_conv���󥹥��󥹤��֤���
 * ��ǡ�smarty�ϤΥ��󥹥��󥹤��֤���褦�˺��ľ������
 *
 * @access public
 * @param string $name �ȡ���������ꤷ���������̾
 * @return conv���󥹥��� �ִ����󥸥󥤥󥹥���
 */
public function get_conv($class_name = 'secure_conv')
{
  //
  $o = new $class_name;

  //
  $this->set_all_to_conv($o);

  //
  return $o;
}

/**
 * radio�ܥ�������ꤹ��
 *
 * @access public
 * @param array $names radio�ܥ���Ȥ������ꤷ������
 * @param conv���󥹥��� $conv �ִ����󥸥󥤥󥹥���
 */
public function set_radio($names, $conv)
{
  foreach($names as $name) {
    conv_util::monoDicChecked($conv, $name, $this->get_value($name));
  }
}



//private:
private $dbh_;          // DB�ϥ�ɥ�

private $tmpname_;      // �ƥ�ݥ��ơ��֥�̾
private $tmp_key_;      // �ƥ�ݥ��ơ��֥��ѥ���

private $tblname_;      // ����DB�ơ��֥�̾(Key��keyname_�ǳ�ǧ)

private $cgi_name_;     // CGI���̾��:hash������̾��
private $tmp_name_;     // �ƥ�ݥ��ơ��֥���̾��:hash������̾��
private $db_name_;      // ����DB���̾��:hash������̾��

private $nokeyname_;    // Key�ǤϤʤ�����̾�켰
private $keyname_;      // Key�ˤʤäƤ�����̾�켰

} // end of class
