<?php

/**
 * CSVデータの１行を表すクラス
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

	// カンマで初期化
	$this->set_separator(",");
}

/**
 * １カラム分のデータをpushする
 *
 * @param string $col
 * @return void
 * @access public
 */
public function push($col) {
	$this->cols_[] = $col;
}

/**
 * カラムのセパレータをセットする
 *
 * @param string $sep
 * @return void
 * @access public
 */
public function set_separator($sep) {
	$this->sep_ = $sep;
}


/**
 * セットされているデータからCSV文字列を作成し返す
 *
 * @param void
 * @return string 
 * @access public
 */
public function get_string() {
	// 「"」をエスケープして、「"」で囲む
	$cols = $this->get_columns();
	foreach ($cols as $key => $val) {
		$cols[$key] = '"' . str_replace('"', '""', $val) . '"';
	}

	// セパレータで区切って復帰
	return implode($this->get_separator(), $cols);
}

//protected:
protected function get_columns() { return $this->cols_; }
protected function get_separator() { return $this->sep_; }


//private:

private $cols_;
private $sep_;


} // end_of_class

