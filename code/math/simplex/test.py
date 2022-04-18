import gurobipy as gp

n, m = map(int, input().split())

model = gp.Model()

v = [i for i in range(n)]
x = model.addVars(v)

for i in range(m):
    a = [0] * n
    for j, s in enumerate(input().split()):
        if j < n:
            a[j] = float(s)
        else:
            b = float(s)

    model.addConstr(sum(x[i] * a[i] for i in range(n)) <= b)
            
c = [0] * n
for i, s in enumerate(input().split()):
    c[i] = float(s)    

model.setObjective(sum(x[i] * c[i] for i in range(n)), gp.GRB.MAXIMIZE)

model.Params.OutputFlag = False
model.optimize()

print(model.getObjective().getValue())
