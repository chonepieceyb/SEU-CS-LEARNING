package DiningHallSimulate;

public abstract interface Visitor {
	public abstract void visit(HangMenJi f);
	public abstract void visit(DiaoZhaBing f);
	public abstract void visit(NiuRouMian f);
}
