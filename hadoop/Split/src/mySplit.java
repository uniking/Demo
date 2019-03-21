import java.util.Iterator;

import org.ansj.domain.Term;
import org.ansj.splitWord.analysis.ToAnalysis;

public class mySplit {

	public static void main(String[] args) throws Exception
	{
		String words = "�й��������Ĵ������Ź�֮һ�������ƾõ���ʷ�����Լ5000��ǰ������ԭ����Ϊ���Ŀ�ʼ���־�����֯�����ɹ��Һͳ���������������ݱ�ͳ�������������ʱ��ϳ��ĳ������ġ��̡��ܡ����������ơ��Ρ�Ԫ��������ȡ���ԭ������ʷ�ϲ����뱱���������彻������ս���ڶ������ںϳ�Ϊ�л����塣20���ͳ������������й��ľ��������˳���ʷ��̨��ȡ����֮���ǹ������塣1949���л����񹲺͹����������й���½����������������ƶȵ����塣�й����Ŷ�ʵ������Ļ�����ͳ������ʽ��ʫ�ʡ�Ϸ�����鷨�͹����ȣ����ڡ�Ԫ�������������硢������������й���Ҫ�Ĵ�ͳ���ա�";  
        //System.out.println(ToAnalysis.parse(words));
        
        Iterator<Term> itor = ToAnalysis.parse(words).iterator();
        
        while(itor.hasNext())
        	System.out.println(itor.next());
	}
}
