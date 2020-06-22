<?xml version="1.0" encoding="GB2312" ?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/TR/WD-xsl">
<xsl:template match="/">
<html>
<head>
<title>查看日志 </title>
<style>
body,BlueIdea,team,blue_ID,blue_name,blue_text,blue_time,blue_class{ font: 14px "宋体", "Arial", "Times New Roman"; } 
table { font-size: 14px; border: 0px double; border-color: #99CC99 #99CC99 #CCCCCC #CCCCCC; cellpadding:3;cellspacing:3; bgcolor:#eeeeee; text-decoration: blink} 
span { font-size: 14px; color: red; }
</style>

<script language="javascript">

//查找记录
function searchtext(FilterValue,FilterItem)
{
	stylesheet=document.XSLDocument;
	source=document.XMLDocument;
	sortField=document.XSLDocument.selectNodes("//@select");
	sortOrderAttribute = document.XMLDocument.selectSingleNode("//@order-by");
	if ( FilterValue != "" )
	{
		sortField[1].value="item[name='" + FilterValue + "']";
		
		if(FilterItem == "name")
		{
			sortField[1].value="item[name='"+FilterValue+"']";
		}
		if(FilterItem == "date")
		{
			sortField[1].value="item[date='"+FilterValue+"']";
		}
		if(FilterItem == "time")
		{
			sortField[1].value="item[time='"+FilterValue+"']";
		}
		if(FilterItem == "level")
		{
			sortField[1].value="item[level='"+FilterValue+"']";
		}
		if(FilterItem == "message")
		{
			sortField[1].value="item[message='"+FilterValue+"']";
		}
		if(FilterItem == "source")
		{
			sortField[1].value="item[source='"+FilterValue+"']";
		}

		Layer1.innerHTML=source.documentElement.transformNode(stylesheet);
	}
	else
	{
		alert("请输入筛选条件！");
	} 
}

//记录排序
clickNum = 0;
oldOrderBy = "+Date";
oldOrder = "Date";
function XmlSort(SortItem) 
{
	if( oldOrder.indexOf(SortItem) != -1 )
	{
	
		if( clickNum % 2 != 0 )
		{
			oldOrderBy = "+" + SortItem;
		}
		else
		{
			oldOrderBy = "-" + SortItem;
		}
		
		clickNum++;
	}
	else
	{
		oldOrderBy = "+" + SortItem;
		
		oldOrder = SortItem;
		clickNum = 0;
	}
	
	
	oldOrder = SortItem;
	SortItem = oldOrderBy;
	
//	alert("SortItem = " + SortItem);
	
	stylesheet=document.XSLDocument; 
	source=document.XMLDocument; 
	sortField=document.XSLDocument.selectSingleNode("//@order-by");
	sortField.value=SortItem;
	Layer1.innerHTML=source.documentElement.transformNode(stylesheet);
}

//分页显示
<xsl:comment> 
<![CDATA[ 

var OnePageNum=50; 
var PageNum=1; 
var XMLPageNum=1; 
function pages(Num) 
{ 
stylesheet=document.XSLDocument; 
source=document.XMLDocument; 
nodes=source.documentElement.childNodes; 
len=nodes.length; 
for(i=1;i<=(len/OnePageNum);i++); 
XMLPageNum=i; 
var firstNum=0; 
var lastNume=0; 

if (Num=="first") {PageNum=1;} 
if (Num=="previous") {if (PageNum>1) PageNum -=1;} 
if (Num=="next") {if (PageNum<XMLPageNum) PageNum +=1;} 
if (Num=="last") {PageNum =XMLPageNum;} 

sortField=document.XSLDocument.selectSingleNode("//@expr"); 
firstNum=OnePageNum*(PageNum-1)+1; 
lastNum=OnePageNum*(PageNum-1)+OnePageNum; 
text="childnumber(this)>="+firstNum+" & childnumber(this)<="+lastNum; 
sortField.value=text; 
Layer1.innerHTML=source.documentElement.transformNode(stylesheet); 
} 
]]> 
</xsl:comment> 


</script>

</head>
<body bgcolor="#f2f2f2">
<p align="center"><span><a href="javascript:document.location.reload()">重新装载</a></span></p>
<div id="Layer1" name="Layer1">
<xsl:apply-templates select="log" />
</div>

  <p align="center"><span>
<table align="center" cellpadding="0" cellspacing="0" border="0" >
<tr>
<td>
<span >请输入筛选条件 : </span>

<select name='Filter' >
    <option value="name" > 名称 </option>
    <option value="date"> 日期 </option>
    <option value="time"> 时间 </option>
    <option value="level"> 级别 </option>
    <option value="message"> 信息 </option>
    <option value="source"> 源文件 </option>
</select>
 = <input type="text" name="searchtext" size="20" maxlength="100" />
<input type="button" class="button" onClick="searchtext(document.all.searchtext.value,document.all.Filter.value)" value="Search" name="button" />
<span >(无条件输入则显示全部内容)</span>
</td>
</tr>
</table>
  </span></p>

<table align="center" width="500" > 
<tr align="center"> 
<td > 
<button id="cmdfirstPage" class="keybutton" onclick="pages('first');" >第一页</button>
<button id="cmdpreviousPage" class="keybutton" onclick="pages('previous');" >上一页</button>  
<button id="cmdnextPage" class="keybutton" onclick="pages('next');">下一页</button>   
<button id="cmdlastPage" class="keybutton" onclick="pages('last');">最后页</button> 
</td> 
</tr> 
</table>  

  <p align="center"><span>
  <br/>View Log 2003，Copy Right by <a href="http://www.neusoft.com">沈阳东软数字医疗系统股份有限公司</a>
  </span></p>
</body>
</html>
</xsl:template>
<xsl:template match="log">
<table width="98%" border="1" align="center" cellpadding="1" cellspacing="1" bordercolordark="#ffffff" bordercolorlight="#ADAAAD">
<tr bgcolor="#FFCC99" align="center">
       <td style="cursor:hand" onclick="XmlSort('name')"><b>名称</b> </td>
       <td style="cursor:hand" onclick="XmlSort('level')" ><b>级别</b> </td>
       <td style="cursor:hand" onclick="XmlSort('date')" ><b>日期</b></td>
       <td style="cursor:hand" onclick="XmlSort('time')" ><b>时间</b></td>
       <td style="cursor:hand" onclick="XmlSort('source')" ><b>源文件</b></td>
       <td style="cursor:hand" onclick="XmlSort('line')" ><b>行数</b></td>
       <td style="cursor:hand" onclick="XmlSort('processid')" ><b>进程ID</b></td>
       <td style="cursor:hand" onclick="XmlSort('threadid')" ><b>线程ID</b></td>
       <td style="cursor:hand" onclick="XmlSort('message')" ><b>信息</b></td>
</tr>

<xsl:apply-templates select="item" order-by="+date"/>

</table>
</xsl:template>
<xsl:template match="item">
<xsl:if expr="childnumber(this)&gt;=1 &amp; childnumber(this)&lt;=50 ">
<tr >
        <td bgcolor="#ffffff" valign="top" align="center"><nobr><xsl:value-of select="name" /></nobr></td>
        
        <td bgcolor="#ffffff" valign="top" align="center">

	<nobr>
	<font>	
	<xsl:attribute name="color">
        	<xsl:choose>
        		<xsl:when test=".[level='INFO']">#0000ff</xsl:when>
        		<xsl:when test=".[level='WARNING']">#ff8000</xsl:when>
        		<xsl:when test=".[level='FINE']">#008800</xsl:when>
        		<xsl:when test=".[level='FINER']">#00cc00</xsl:when>
        		<xsl:when test=".[level='FINEST']">#00FF00</xsl:when>
        		<xsl:when test=".[level='SEVERE']">#ff0000</xsl:when>
        		<xsl:when test=".[level='CONFIG']">#000000</xsl:when>
        		<xsl:otherwise>#800000</xsl:otherwise>
        	</xsl:choose>
        </xsl:attribute>
        
        <xsl:value-of select="level" />
        </font>
        </nobr>

        </td>
        <td bgcolor="#ffffff" valign="top" align="center"><nobr><xsl:value-of select="date" /></nobr></td>
        <td bgcolor="#ffffff" valign="top" align="center"><nobr><xsl:value-of select="time" /></nobr></td>
        <td bgcolor="#ffffff" valign="top" align="left"><nobr><xsl:value-of select="source" /></nobr></td>
        <td bgcolor="#ffffff" valign="top"> <xsl:value-of select="line" /></td>
        <td bgcolor="#ffffff" valign="top"> <xsl:value-of select="processid" /></td>
        <td bgcolor="#ffffff" valign="top"> <xsl:value-of select="threadid" /></td>
        <td bgcolor="#ffffff" valign="top"> <xsl:value-of select="message" /></td>
</tr>
</xsl:if>

</xsl:template>
<xsl:template match="name">
<td bgcolor="#eeeeee">
<xsl:value-of />
</td>
</xsl:template>
<xsl:template match="level">
<td bgcolor="#eeeeee">
<xsl:value-of />
</td>
</xsl:template>
<xsl:template match="date">
<td>
<xsl:value-of />
</td>
</xsl:template>
<xsl:template match="time">
<td>
<xsl:value-of />
</td>
</xsl:template>
<xsl:template match="source">
<td>
<xsl:value-of />
</td>
</xsl:template>
<xsl:template match="line">
<td>
<xsl:value-of />
</td>
</xsl:template>
<xsl:template match="processid">
<td>
<xsl:value-of />
</td>
</xsl:template>
<xsl:template match="threadid">
<td>
<xsl:value-of />
</td>
</xsl:template>
<xsl:template match="message">
<td>
<xsl:value-of />
</td>
</xsl:template>
</xsl:stylesheet>