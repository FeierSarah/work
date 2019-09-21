package student;

public class Count{
	public float getMaleAverAge(Student[] students,String major)
		{
			float sum=0.0f;
			int count=0;
			int i=0;
			for( i=0;i<students.length;i++)
			{
				if(students[i].major.equals(major))
				{
				    if(students[i].sex.equals("male"))
				    {
					    ++count;
					    sum+=students[i].age;
				    }
			    }
			}
			return sum/count;
		}
	public int getSexCount(Student[] students,String major)
	{
		int count=0;
		int i=0;
		for(i=0;i<students.length;i++)
		{
			if(students[i].major.equals(major))
			{
			    if(students[i].sex.equals("male"))
			    {
				    ++count;
			    }
		    }
		}
		return count;
	}
}
