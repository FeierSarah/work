package student;

public class Test {
    public static void main(String[] args){
		Student[] students=new Student[12];
		String[] names1={"王","丁","杜","段","许","欧阳"};
		String[] names2={"易","郑","朴","肖","李","刘"};
		String[] major1={"中文","数学","英语","英语","中文","中文"};
		String[] major2={"英语","数学","中文","英语","中文","数学"};
		int[] ages1={19,20,18,21,22,20};
		int[] ages2={20,21,22,18,19,19};
		for(int i=0;i<names1.length;i++)
		{
			students[i]=new Student();
			students[i].name=names1[i];
			students[i].sex="female";
			students[i].age=ages1[i];
			students[i].num=i+1;
			students[i].major=major1[i];
		}
		for(int i=names1.length;i<names1.length+names2.length;i++)
		{
			students[i]=new Student();
			students[i].name=names2[i-names1.length];
			students[i].sex="male";
			students[i].age=ages2[i-names1.length];
			students[i].num=i+i;
			students[i].major=major2[i-names1.length];
		}
	   Count deal=new Count();
	   int count1=deal.getSexCount(students, "中文");
	   int count2=deal.getSexCount(students, "数学");
	   int count3=deal.getSexCount(students, "英语");
       float a1=deal.getMaleAverAge(students, "中文");
       float a2=deal.getMaleAverAge(students, "数学");
       float a3=deal.getMaleAverAge(students, "英语");
       System.out.println("中文专业男生有"+count1+"个人且平均年龄为"+a1);
       System.out.println("数学专业男生有"+count2+"个人且平均年龄为"+a2);
       System.out.println("英语专业男生有"+count3+"个人且平均年龄为"+a3);
	}
}