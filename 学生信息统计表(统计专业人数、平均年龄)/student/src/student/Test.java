package student;

public class Test {
    public static void main(String[] args){
		Student[] students=new Student[12];
		String[] names1={"��","��","��","��","��","ŷ��"};
		String[] names2={"��","֣","��","Ф","��","��"};
		String[] major1={"����","��ѧ","Ӣ��","Ӣ��","����","����"};
		String[] major2={"Ӣ��","��ѧ","����","Ӣ��","����","��ѧ"};
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
	   int count1=deal.getSexCount(students, "����");
	   int count2=deal.getSexCount(students, "��ѧ");
	   int count3=deal.getSexCount(students, "Ӣ��");
       float a1=deal.getMaleAverAge(students, "����");
       float a2=deal.getMaleAverAge(students, "��ѧ");
       float a3=deal.getMaleAverAge(students, "Ӣ��");
       System.out.println("����רҵ������"+count1+"������ƽ������Ϊ"+a1);
       System.out.println("��ѧרҵ������"+count2+"������ƽ������Ϊ"+a2);
       System.out.println("Ӣ��רҵ������"+count3+"������ƽ������Ϊ"+a3);
	}
}