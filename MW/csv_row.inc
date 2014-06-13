<?php

/**
 * CSV�ǡ����Σ��Ԥ�ɽ�����饹
 *
 *
 * @package magicweapon
 * @access  public
 * @author  Kohei Yamada <hecomark@gmail.com>
 * @create  2007/07/28
 * @version $Id$
 **/

class csv_row
{
//public:

public function __construct() { $this->init(); }
public function init() {
	$this->cols_ = array();
	$this->sep_ = "";

	// ����ޤǽ����
	$this->set_separator(",");
}

/**
 * �������ʬ�Υǡ�����push����
 *
 * @param string $col
 * @return void
 * @access public
 */
public function push($col) {
	$this->cols_[] = $col;
}

/**
 * �����Υ��ѥ졼���򥻥åȤ���
 *
 * @param string $sep
 * @return void
 * @access public
 */
public function set_separator($sep) {
	$this->sep_ = $sep;
}


/**
 * ���åȤ���Ƥ���ǡ�������CSVʸ�����������֤�
 *
 * @param void
 * @return string 
 * @access public
 */
public function get_string() {
	// ��"�פ򥨥������פ��ơ���"�פǰϤ�
	$cols = $this->get_columns();
	foreach ($cols as $key => $val) {
		$cols[$key] = '"' . str_replace('"', '""', $val) . '"';
	}

	// ���ѥ졼���Ƕ��ڤä�����
	return implode($this->get_separator(), $cols);
}

//protected:
protected function get_columns() { return $this->cols_; }
protected function get_separator() { return $this->sep_; }


//private:

private $cols_;
private $sep_;


} // end_of_class
