??
??
B
AssignVariableOp
resource
value"dtype"
dtypetype?
~
BiasAdd

value"T	
bias"T
output"T" 
Ttype:
2	"-
data_formatstringNHWC:
NHWCNCHW
8
Const
output"dtype"
valuetensor"
dtypetype
?
Conv2D

input"T
filter"T
output"T"
Ttype:	
2"
strides	list(int)"
use_cudnn_on_gpubool(",
paddingstring:
SAMEVALIDEXPLICIT""
explicit_paddings	list(int)
 "-
data_formatstringNHWC:
NHWCNCHW" 
	dilations	list(int)

?
FusedBatchNormV3
x"T

scale"U
offset"U	
mean"U
variance"U
y"T

batch_mean"U
batch_variance"U
reserve_space_1"U
reserve_space_2"U
reserve_space_3"U"
Ttype:
2"
Utype:
2"
epsilonfloat%??8"&
exponential_avg_factorfloat%  ??";
data_formatstringNHWC:
NHWCNCHWNDHWCNCDHW"
is_trainingbool(
.
Identity

input"T
output"T"	
Ttype
q
MatMul
a"T
b"T
product"T"
transpose_abool( "
transpose_bbool( "
Ttype:

2	
?
MaxPool

input"T
output"T"
Ttype0:
2	"
ksize	list(int)(0"
strides	list(int)(0",
paddingstring:
SAMEVALIDEXPLICIT""
explicit_paddings	list(int)
 ":
data_formatstringNHWC:
NHWCNCHWNCHW_VECT_C
e
MergeV2Checkpoints
checkpoint_prefixes
destination_prefix"
delete_old_dirsbool(?

NoOp
M
Pack
values"T*N
output"T"
Nint(0"	
Ttype"
axisint 
C
Placeholder
output"dtype"
dtypetype"
shapeshape:
@
ReadVariableOp
resource
value"dtype"
dtypetype?
E
Relu
features"T
activations"T"
Ttype:
2	
[
Reshape
tensor"T
shape"Tshape
output"T"	
Ttype"
Tshapetype0:
2	
o
	RestoreV2

prefix
tensor_names
shape_and_slices
tensors2dtypes"
dtypes
list(type)(0?
l
SaveV2

prefix
tensor_names
shape_and_slices
tensors2dtypes"
dtypes
list(type)(0?
?
Select
	condition

t"T
e"T
output"T"	
Ttype
H
ShardedFilename
basename	
shard

num_shards
filename
9
Softmax
logits"T
softmax"T"
Ttype:
2
?
StatefulPartitionedCall
args2Tin
output2Tout"
Tin
list(type)("
Tout
list(type)("	
ffunc"
configstring "
config_protostring "
executor_typestring ?
@
StaticRegexFullMatch	
input

output
"
patternstring
N

StringJoin
inputs*N

output"
Nint(0"
	separatorstring 
?
VarHandleOp
resource"
	containerstring "
shared_namestring "
dtypetype"
shapeshape"#
allowed_deviceslist(string)
 ?"serve*2.5.02v2.5.0-rc3-213-ga4dfb8d1a718??
?
conv2d_20/kernelVarHandleOp*
_output_shapes
: *
dtype0*
shape: *!
shared_nameconv2d_20/kernel
}
$conv2d_20/kernel/Read/ReadVariableOpReadVariableOpconv2d_20/kernel*&
_output_shapes
: *
dtype0
t
conv2d_20/biasVarHandleOp*
_output_shapes
: *
dtype0*
shape: *
shared_nameconv2d_20/bias
m
"conv2d_20/bias/Read/ReadVariableOpReadVariableOpconv2d_20/bias*
_output_shapes
: *
dtype0
{
dense_40/kernelVarHandleOp*
_output_shapes
: *
dtype0*
shape:	?*d* 
shared_namedense_40/kernel
t
#dense_40/kernel/Read/ReadVariableOpReadVariableOpdense_40/kernel*
_output_shapes
:	?*d*
dtype0
r
dense_40/biasVarHandleOp*
_output_shapes
: *
dtype0*
shape:d*
shared_namedense_40/bias
k
!dense_40/bias/Read/ReadVariableOpReadVariableOpdense_40/bias*
_output_shapes
:d*
dtype0
z
dense_41/kernelVarHandleOp*
_output_shapes
: *
dtype0*
shape
:d
* 
shared_namedense_41/kernel
s
#dense_41/kernel/Read/ReadVariableOpReadVariableOpdense_41/kernel*
_output_shapes

:d
*
dtype0
r
dense_41/biasVarHandleOp*
_output_shapes
: *
dtype0*
shape:
*
shared_namedense_41/bias
k
!dense_41/bias/Read/ReadVariableOpReadVariableOpdense_41/bias*
_output_shapes
:
*
dtype0
?
.module_wrapper_14/batch_normalization_14/gammaVarHandleOp*
_output_shapes
: *
dtype0*
shape: *?
shared_name0.module_wrapper_14/batch_normalization_14/gamma
?
Bmodule_wrapper_14/batch_normalization_14/gamma/Read/ReadVariableOpReadVariableOp.module_wrapper_14/batch_normalization_14/gamma*
_output_shapes
: *
dtype0
?
-module_wrapper_14/batch_normalization_14/betaVarHandleOp*
_output_shapes
: *
dtype0*
shape: *>
shared_name/-module_wrapper_14/batch_normalization_14/beta
?
Amodule_wrapper_14/batch_normalization_14/beta/Read/ReadVariableOpReadVariableOp-module_wrapper_14/batch_normalization_14/beta*
_output_shapes
: *
dtype0
?
4module_wrapper_14/batch_normalization_14/moving_meanVarHandleOp*
_output_shapes
: *
dtype0*
shape: *E
shared_name64module_wrapper_14/batch_normalization_14/moving_mean
?
Hmodule_wrapper_14/batch_normalization_14/moving_mean/Read/ReadVariableOpReadVariableOp4module_wrapper_14/batch_normalization_14/moving_mean*
_output_shapes
: *
dtype0
?
8module_wrapper_14/batch_normalization_14/moving_varianceVarHandleOp*
_output_shapes
: *
dtype0*
shape: *I
shared_name:8module_wrapper_14/batch_normalization_14/moving_variance
?
Lmodule_wrapper_14/batch_normalization_14/moving_variance/Read/ReadVariableOpReadVariableOp8module_wrapper_14/batch_normalization_14/moving_variance*
_output_shapes
: *
dtype0
^
totalVarHandleOp*
_output_shapes
: *
dtype0*
shape: *
shared_nametotal
W
total/Read/ReadVariableOpReadVariableOptotal*
_output_shapes
: *
dtype0
^
countVarHandleOp*
_output_shapes
: *
dtype0*
shape: *
shared_namecount
W
count/Read/ReadVariableOpReadVariableOpcount*
_output_shapes
: *
dtype0
b
total_1VarHandleOp*
_output_shapes
: *
dtype0*
shape: *
shared_name	total_1
[
total_1/Read/ReadVariableOpReadVariableOptotal_1*
_output_shapes
: *
dtype0
b
count_1VarHandleOp*
_output_shapes
: *
dtype0*
shape: *
shared_name	count_1
[
count_1/Read/ReadVariableOpReadVariableOpcount_1*
_output_shapes
: *
dtype0

NoOpNoOp
?#
ConstConst"/device:CPU:0*
_output_shapes
: *
dtype0*?#
value?#B?# B?#
?
layer_with_weights-0
layer-0
layer_with_weights-1
layer-1
layer-2
layer-3
layer_with_weights-2
layer-4
layer_with_weights-3
layer-5
	optimizer
regularization_losses
		variables

trainable_variables
	keras_api

signatures
h

kernel
bias
regularization_losses
	variables
trainable_variables
	keras_api
_
_module
regularization_losses
	variables
trainable_variables
	keras_api
R
regularization_losses
	variables
trainable_variables
	keras_api
R
regularization_losses
	variables
trainable_variables
	keras_api
h

 kernel
!bias
"regularization_losses
#	variables
$trainable_variables
%	keras_api
h

&kernel
'bias
(regularization_losses
)	variables
*trainable_variables
+	keras_api
 
 
F
0
1
,2
-3
.4
/5
 6
!7
&8
'9
8
0
1
,2
-3
 4
!5
&6
'7
?
0metrics
1layer_regularization_losses
2layer_metrics
regularization_losses

3layers
		variables

trainable_variables
4non_trainable_variables
 
\Z
VARIABLE_VALUEconv2d_20/kernel6layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUE
XV
VARIABLE_VALUEconv2d_20/bias4layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUE
 

0
1

0
1
?
5layer_regularization_losses
6non_trainable_variables
7layer_metrics
regularization_losses

8layers
	variables
trainable_variables
9metrics
?
:axis
	,gamma
-beta
.moving_mean
/moving_variance
;regularization_losses
<	variables
=trainable_variables
>	keras_api
 

,0
-1
.2
/3

,0
-1
?
?layer_regularization_losses
@non_trainable_variables
Alayer_metrics
regularization_losses

Blayers
	variables
trainable_variables
Cmetrics
 
 
 
?
Dlayer_regularization_losses
Enon_trainable_variables
Flayer_metrics
regularization_losses

Glayers
	variables
trainable_variables
Hmetrics
 
 
 
?
Ilayer_regularization_losses
Jnon_trainable_variables
Klayer_metrics
regularization_losses

Llayers
	variables
trainable_variables
Mmetrics
[Y
VARIABLE_VALUEdense_40/kernel6layer_with_weights-2/kernel/.ATTRIBUTES/VARIABLE_VALUE
WU
VARIABLE_VALUEdense_40/bias4layer_with_weights-2/bias/.ATTRIBUTES/VARIABLE_VALUE
 

 0
!1

 0
!1
?
Nlayer_regularization_losses
Onon_trainable_variables
Player_metrics
"regularization_losses

Qlayers
#	variables
$trainable_variables
Rmetrics
[Y
VARIABLE_VALUEdense_41/kernel6layer_with_weights-3/kernel/.ATTRIBUTES/VARIABLE_VALUE
WU
VARIABLE_VALUEdense_41/bias4layer_with_weights-3/bias/.ATTRIBUTES/VARIABLE_VALUE
 

&0
'1

&0
'1
?
Slayer_regularization_losses
Tnon_trainable_variables
Ulayer_metrics
(regularization_losses

Vlayers
)	variables
*trainable_variables
Wmetrics
jh
VARIABLE_VALUE.module_wrapper_14/batch_normalization_14/gamma&variables/2/.ATTRIBUTES/VARIABLE_VALUE
ig
VARIABLE_VALUE-module_wrapper_14/batch_normalization_14/beta&variables/3/.ATTRIBUTES/VARIABLE_VALUE
pn
VARIABLE_VALUE4module_wrapper_14/batch_normalization_14/moving_mean&variables/4/.ATTRIBUTES/VARIABLE_VALUE
tr
VARIABLE_VALUE8module_wrapper_14/batch_normalization_14/moving_variance&variables/5/.ATTRIBUTES/VARIABLE_VALUE

X0
Y1
 
 
*
0
1
2
3
4
5

.0
/1
 
 
 
 
 
 
 

,0
-1
.2
/3

,0
-1
?
Zlayer_regularization_losses
[non_trainable_variables
\layer_metrics
;regularization_losses

]layers
<	variables
=trainable_variables
^metrics
 

.0
/1
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
4
	_total
	`count
a	variables
b	keras_api
D
	ctotal
	dcount
e
_fn_kwargs
f	variables
g	keras_api
 

.0
/1
 
 
 
OM
VARIABLE_VALUEtotal4keras_api/metrics/0/total/.ATTRIBUTES/VARIABLE_VALUE
OM
VARIABLE_VALUEcount4keras_api/metrics/0/count/.ATTRIBUTES/VARIABLE_VALUE

_0
`1

a	variables
QO
VARIABLE_VALUEtotal_14keras_api/metrics/1/total/.ATTRIBUTES/VARIABLE_VALUE
QO
VARIABLE_VALUEcount_14keras_api/metrics/1/count/.ATTRIBUTES/VARIABLE_VALUE
 

c0
d1

f	variables
?
serving_default_conv2d_20_inputPlaceholder*/
_output_shapes
:?????????*
dtype0*$
shape:?????????
?
StatefulPartitionedCallStatefulPartitionedCallserving_default_conv2d_20_inputconv2d_20/kernelconv2d_20/bias.module_wrapper_14/batch_normalization_14/gamma-module_wrapper_14/batch_normalization_14/beta4module_wrapper_14/batch_normalization_14/moving_mean8module_wrapper_14/batch_normalization_14/moving_variancedense_40/kerneldense_40/biasdense_41/kerneldense_41/bias*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????
*,
_read_only_resource_inputs

	
*-
config_proto

CPU

GPU 2J 8? *-
f(R&
$__inference_signature_wrapper_758248
O
saver_filenamePlaceholder*
_output_shapes
: *
dtype0*
shape: 
?
StatefulPartitionedCall_1StatefulPartitionedCallsaver_filename$conv2d_20/kernel/Read/ReadVariableOp"conv2d_20/bias/Read/ReadVariableOp#dense_40/kernel/Read/ReadVariableOp!dense_40/bias/Read/ReadVariableOp#dense_41/kernel/Read/ReadVariableOp!dense_41/bias/Read/ReadVariableOpBmodule_wrapper_14/batch_normalization_14/gamma/Read/ReadVariableOpAmodule_wrapper_14/batch_normalization_14/beta/Read/ReadVariableOpHmodule_wrapper_14/batch_normalization_14/moving_mean/Read/ReadVariableOpLmodule_wrapper_14/batch_normalization_14/moving_variance/Read/ReadVariableOptotal/Read/ReadVariableOpcount/Read/ReadVariableOptotal_1/Read/ReadVariableOpcount_1/Read/ReadVariableOpConst*
Tin
2*
Tout
2*
_collective_manager_ids
 *
_output_shapes
: * 
_read_only_resource_inputs
 *-
config_proto

CPU

GPU 2J 8? *(
f#R!
__inference__traced_save_758768
?
StatefulPartitionedCall_2StatefulPartitionedCallsaver_filenameconv2d_20/kernelconv2d_20/biasdense_40/kerneldense_40/biasdense_41/kerneldense_41/bias.module_wrapper_14/batch_normalization_14/gamma-module_wrapper_14/batch_normalization_14/beta4module_wrapper_14/batch_normalization_14/moving_mean8module_wrapper_14/batch_normalization_14/moving_variancetotalcounttotal_1count_1*
Tin
2*
Tout
2*
_collective_manager_ids
 *
_output_shapes
: * 
_read_only_resource_inputs
 *-
config_proto

CPU

GPU 2J 8? *+
f&R$
"__inference__traced_restore_758820??
?
?
7__inference_batch_normalization_14_layer_call_fn_758703

inputs
unknown: 
	unknown_0: 
	unknown_1: 
	unknown_2: 
identity??StatefulPartitionedCall?
StatefulPartitionedCallStatefulPartitionedCallinputsunknown	unknown_0	unknown_1	unknown_2*
Tin	
2*
Tout
2*
_collective_manager_ids
 *A
_output_shapes/
-:+??????????????????????????? *$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *[
fVRT
R__inference_batch_normalization_14_layer_call_and_return_conditional_losses_7583142
StatefulPartitionedCall?
IdentityIdentity StatefulPartitionedCall:output:0^StatefulPartitionedCall*
T0*A
_output_shapes/
-:+??????????????????????????? 2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*H
_input_shapes7
5:+??????????????????????????? : : : : 22
StatefulPartitionedCallStatefulPartitionedCall:i e
A
_output_shapes/
-:+??????????????????????????? 
 
_user_specified_nameinputs
?
h
L__inference_max_pooling2d_20_layer_call_and_return_conditional_losses_757850

inputs
identity?
MaxPoolMaxPoolinputs*J
_output_shapes8
6:4????????????????????????????????????*
ksize
*
paddingVALID*
strides
2	
MaxPool?
IdentityIdentityMaxPool:output:0*
T0*J
_output_shapes8
6:4????????????????????????????????????2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*I
_input_shapes8
6:4????????????????????????????????????:r n
J
_output_shapes8
6:4????????????????????????????????????
 
_user_specified_nameinputs
?

?
.__inference_sequential_20_layer_call_fn_758508

inputs!
unknown: 
	unknown_0: 
	unknown_1: 
	unknown_2: 
	unknown_3: 
	unknown_4: 
	unknown_5:	?*d
	unknown_6:d
	unknown_7:d

	unknown_8:

identity??StatefulPartitionedCall?
StatefulPartitionedCallStatefulPartitionedCallinputsunknown	unknown_0	unknown_1	unknown_2	unknown_3	unknown_4	unknown_5	unknown_6	unknown_7	unknown_8*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????
**
_read_only_resource_inputs

	
*-
config_proto

CPU

GPU 2J 8? *R
fMRK
I__inference_sequential_20_layer_call_and_return_conditional_losses_7581132
StatefulPartitionedCall?
IdentityIdentity StatefulPartitionedCall:output:0^StatefulPartitionedCall*
T0*'
_output_shapes
:?????????
2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*B
_input_shapes1
/:?????????: : : : : : : : : : 22
StatefulPartitionedCallStatefulPartitionedCall:W S
/
_output_shapes
:?????????
 
_user_specified_nameinputs
? 
?
I__inference_sequential_20_layer_call_and_return_conditional_losses_758221
conv2d_20_input*
conv2d_20_758194: 
conv2d_20_758196: &
module_wrapper_14_758199: &
module_wrapper_14_758201: &
module_wrapper_14_758203: &
module_wrapper_14_758205: "
dense_40_758210:	?*d
dense_40_758212:d!
dense_41_758215:d

dense_41_758217:

identity??!conv2d_20/StatefulPartitionedCall? dense_40/StatefulPartitionedCall? dense_41/StatefulPartitionedCall?)module_wrapper_14/StatefulPartitionedCall?
!conv2d_20/StatefulPartitionedCallStatefulPartitionedCallconv2d_20_inputconv2d_20_758194conv2d_20_758196*
Tin
2*
Tout
2*
_collective_manager_ids
 */
_output_shapes
:????????? *$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *N
fIRG
E__inference_conv2d_20_layer_call_and_return_conditional_losses_7578742#
!conv2d_20/StatefulPartitionedCall?
)module_wrapper_14/StatefulPartitionedCallStatefulPartitionedCall*conv2d_20/StatefulPartitionedCall:output:0module_wrapper_14_758199module_wrapper_14_758201module_wrapper_14_758203module_wrapper_14_758205*
Tin	
2*
Tout
2*
_collective_manager_ids
 */
_output_shapes
:????????? *$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *V
fQRO
M__inference_module_wrapper_14_layer_call_and_return_conditional_losses_7580352+
)module_wrapper_14/StatefulPartitionedCall?
 max_pooling2d_20/PartitionedCallPartitionedCall2module_wrapper_14/StatefulPartitionedCall:output:0*
Tin
2*
Tout
2*
_collective_manager_ids
 */
_output_shapes
:????????? * 
_read_only_resource_inputs
 *-
config_proto

CPU

GPU 2J 8? *U
fPRN
L__inference_max_pooling2d_20_layer_call_and_return_conditional_losses_7578502"
 max_pooling2d_20/PartitionedCall?
flatten_20/PartitionedCallPartitionedCall)max_pooling2d_20/PartitionedCall:output:0*
Tin
2*
Tout
2*
_collective_manager_ids
 *(
_output_shapes
:??????????** 
_read_only_resource_inputs
 *-
config_proto

CPU

GPU 2J 8? *O
fJRH
F__inference_flatten_20_layer_call_and_return_conditional_losses_7579152
flatten_20/PartitionedCall?
 dense_40/StatefulPartitionedCallStatefulPartitionedCall#flatten_20/PartitionedCall:output:0dense_40_758210dense_40_758212*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????d*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *M
fHRF
D__inference_dense_40_layer_call_and_return_conditional_losses_7579282"
 dense_40/StatefulPartitionedCall?
 dense_41/StatefulPartitionedCallStatefulPartitionedCall)dense_40/StatefulPartitionedCall:output:0dense_41_758215dense_41_758217*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????
*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *M
fHRF
D__inference_dense_41_layer_call_and_return_conditional_losses_7579452"
 dense_41/StatefulPartitionedCall?
IdentityIdentity)dense_41/StatefulPartitionedCall:output:0"^conv2d_20/StatefulPartitionedCall!^dense_40/StatefulPartitionedCall!^dense_41/StatefulPartitionedCall*^module_wrapper_14/StatefulPartitionedCall*
T0*'
_output_shapes
:?????????
2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*B
_input_shapes1
/:?????????: : : : : : : : : : 2F
!conv2d_20/StatefulPartitionedCall!conv2d_20/StatefulPartitionedCall2D
 dense_40/StatefulPartitionedCall dense_40/StatefulPartitionedCall2D
 dense_41/StatefulPartitionedCall dense_41/StatefulPartitionedCall2V
)module_wrapper_14/StatefulPartitionedCall)module_wrapper_14/StatefulPartitionedCall:` \
/
_output_shapes
:?????????
)
_user_specified_nameconv2d_20_input
?
?
E__inference_conv2d_20_layer_call_and_return_conditional_losses_758519

inputs8
conv2d_readvariableop_resource: -
biasadd_readvariableop_resource: 
identity??BiasAdd/ReadVariableOp?Conv2D/ReadVariableOp?
Conv2D/ReadVariableOpReadVariableOpconv2d_readvariableop_resource*&
_output_shapes
: *
dtype02
Conv2D/ReadVariableOp?
Conv2DConv2DinputsConv2D/ReadVariableOp:value:0*
T0*/
_output_shapes
:????????? *
paddingVALID*
strides
2
Conv2D?
BiasAdd/ReadVariableOpReadVariableOpbiasadd_readvariableop_resource*
_output_shapes
: *
dtype02
BiasAdd/ReadVariableOp?
BiasAddBiasAddConv2D:output:0BiasAdd/ReadVariableOp:value:0*
T0*/
_output_shapes
:????????? 2	
BiasAdd`
ReluReluBiasAdd:output:0*
T0*/
_output_shapes
:????????? 2
Relu?
IdentityIdentityRelu:activations:0^BiasAdd/ReadVariableOp^Conv2D/ReadVariableOp*
T0*/
_output_shapes
:????????? 2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*2
_input_shapes!
:?????????: : 20
BiasAdd/ReadVariableOpBiasAdd/ReadVariableOp2.
Conv2D/ReadVariableOpConv2D/ReadVariableOp:W S
/
_output_shapes
:?????????
 
_user_specified_nameinputs
?
?
7__inference_batch_normalization_14_layer_call_fn_758690

inputs
unknown: 
	unknown_0: 
	unknown_1: 
	unknown_2: 
identity??StatefulPartitionedCall?
StatefulPartitionedCallStatefulPartitionedCallinputsunknown	unknown_0	unknown_1	unknown_2*
Tin	
2*
Tout
2*
_collective_manager_ids
 *A
_output_shapes/
-:+??????????????????????????? *&
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *[
fVRT
R__inference_batch_normalization_14_layer_call_and_return_conditional_losses_7582702
StatefulPartitionedCall?
IdentityIdentity StatefulPartitionedCall:output:0^StatefulPartitionedCall*
T0*A
_output_shapes/
-:+??????????????????????????? 2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*H
_input_shapes7
5:+??????????????????????????? : : : : 22
StatefulPartitionedCallStatefulPartitionedCall:i e
A
_output_shapes/
-:+??????????????????????????? 
 
_user_specified_nameinputs
?
?
R__inference_batch_normalization_14_layer_call_and_return_conditional_losses_758314

inputs%
readvariableop_resource: '
readvariableop_1_resource: 6
(fusedbatchnormv3_readvariableop_resource: 8
*fusedbatchnormv3_readvariableop_1_resource: 
identity??AssignNewValue?AssignNewValue_1?FusedBatchNormV3/ReadVariableOp?!FusedBatchNormV3/ReadVariableOp_1?ReadVariableOp?ReadVariableOp_1t
ReadVariableOpReadVariableOpreadvariableop_resource*
_output_shapes
: *
dtype02
ReadVariableOpz
ReadVariableOp_1ReadVariableOpreadvariableop_1_resource*
_output_shapes
: *
dtype02
ReadVariableOp_1?
FusedBatchNormV3/ReadVariableOpReadVariableOp(fusedbatchnormv3_readvariableop_resource*
_output_shapes
: *
dtype02!
FusedBatchNormV3/ReadVariableOp?
!FusedBatchNormV3/ReadVariableOp_1ReadVariableOp*fusedbatchnormv3_readvariableop_1_resource*
_output_shapes
: *
dtype02#
!FusedBatchNormV3/ReadVariableOp_1?
FusedBatchNormV3FusedBatchNormV3inputsReadVariableOp:value:0ReadVariableOp_1:value:0'FusedBatchNormV3/ReadVariableOp:value:0)FusedBatchNormV3/ReadVariableOp_1:value:0*
T0*
U0*]
_output_shapesK
I:+??????????????????????????? : : : : :*
epsilon%o?:*
exponential_avg_factor%
?#<2
FusedBatchNormV3?
AssignNewValueAssignVariableOp(fusedbatchnormv3_readvariableop_resourceFusedBatchNormV3:batch_mean:0 ^FusedBatchNormV3/ReadVariableOp*
_output_shapes
 *
dtype02
AssignNewValue?
AssignNewValue_1AssignVariableOp*fusedbatchnormv3_readvariableop_1_resource!FusedBatchNormV3:batch_variance:0"^FusedBatchNormV3/ReadVariableOp_1*
_output_shapes
 *
dtype02
AssignNewValue_1?
IdentityIdentityFusedBatchNormV3:y:0^AssignNewValue^AssignNewValue_1 ^FusedBatchNormV3/ReadVariableOp"^FusedBatchNormV3/ReadVariableOp_1^ReadVariableOp^ReadVariableOp_1*
T0*A
_output_shapes/
-:+??????????????????????????? 2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*H
_input_shapes7
5:+??????????????????????????? : : : : 2 
AssignNewValueAssignNewValue2$
AssignNewValue_1AssignNewValue_12B
FusedBatchNormV3/ReadVariableOpFusedBatchNormV3/ReadVariableOp2F
!FusedBatchNormV3/ReadVariableOp_1!FusedBatchNormV3/ReadVariableOp_12 
ReadVariableOpReadVariableOp2$
ReadVariableOp_1ReadVariableOp_1:i e
A
_output_shapes/
-:+??????????????????????????? 
 
_user_specified_nameinputs
?
?
2__inference_module_wrapper_14_layer_call_fn_758590

args_0
unknown: 
	unknown_0: 
	unknown_1: 
	unknown_2: 
identity??StatefulPartitionedCall?
StatefulPartitionedCallStatefulPartitionedCallargs_0unknown	unknown_0	unknown_1	unknown_2*
Tin	
2*
Tout
2*
_collective_manager_ids
 */
_output_shapes
:????????? *$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *V
fQRO
M__inference_module_wrapper_14_layer_call_and_return_conditional_losses_7580352
StatefulPartitionedCall?
IdentityIdentity StatefulPartitionedCall:output:0^StatefulPartitionedCall*
T0*/
_output_shapes
:????????? 2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*6
_input_shapes%
#:????????? : : : : 22
StatefulPartitionedCallStatefulPartitionedCall:W S
/
_output_shapes
:????????? 
 
_user_specified_nameargs_0
?
?
M__inference_module_wrapper_14_layer_call_and_return_conditional_losses_758564

args_0<
.batch_normalization_14_readvariableop_resource: >
0batch_normalization_14_readvariableop_1_resource: M
?batch_normalization_14_fusedbatchnormv3_readvariableop_resource: O
Abatch_normalization_14_fusedbatchnormv3_readvariableop_1_resource: 
identity??%batch_normalization_14/AssignNewValue?'batch_normalization_14/AssignNewValue_1?6batch_normalization_14/FusedBatchNormV3/ReadVariableOp?8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1?%batch_normalization_14/ReadVariableOp?'batch_normalization_14/ReadVariableOp_1?
%batch_normalization_14/ReadVariableOpReadVariableOp.batch_normalization_14_readvariableop_resource*
_output_shapes
: *
dtype02'
%batch_normalization_14/ReadVariableOp?
'batch_normalization_14/ReadVariableOp_1ReadVariableOp0batch_normalization_14_readvariableop_1_resource*
_output_shapes
: *
dtype02)
'batch_normalization_14/ReadVariableOp_1?
6batch_normalization_14/FusedBatchNormV3/ReadVariableOpReadVariableOp?batch_normalization_14_fusedbatchnormv3_readvariableop_resource*
_output_shapes
: *
dtype028
6batch_normalization_14/FusedBatchNormV3/ReadVariableOp?
8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1ReadVariableOpAbatch_normalization_14_fusedbatchnormv3_readvariableop_1_resource*
_output_shapes
: *
dtype02:
8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1?
'batch_normalization_14/FusedBatchNormV3FusedBatchNormV3args_0-batch_normalization_14/ReadVariableOp:value:0/batch_normalization_14/ReadVariableOp_1:value:0>batch_normalization_14/FusedBatchNormV3/ReadVariableOp:value:0@batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1:value:0*
T0*
U0*K
_output_shapes9
7:????????? : : : : :*
epsilon%o?:*
exponential_avg_factor%
?#<2)
'batch_normalization_14/FusedBatchNormV3?
%batch_normalization_14/AssignNewValueAssignVariableOp?batch_normalization_14_fusedbatchnormv3_readvariableop_resource4batch_normalization_14/FusedBatchNormV3:batch_mean:07^batch_normalization_14/FusedBatchNormV3/ReadVariableOp*
_output_shapes
 *
dtype02'
%batch_normalization_14/AssignNewValue?
'batch_normalization_14/AssignNewValue_1AssignVariableOpAbatch_normalization_14_fusedbatchnormv3_readvariableop_1_resource8batch_normalization_14/FusedBatchNormV3:batch_variance:09^batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1*
_output_shapes
 *
dtype02)
'batch_normalization_14/AssignNewValue_1?
IdentityIdentity+batch_normalization_14/FusedBatchNormV3:y:0&^batch_normalization_14/AssignNewValue(^batch_normalization_14/AssignNewValue_17^batch_normalization_14/FusedBatchNormV3/ReadVariableOp9^batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1&^batch_normalization_14/ReadVariableOp(^batch_normalization_14/ReadVariableOp_1*
T0*/
_output_shapes
:????????? 2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*6
_input_shapes%
#:????????? : : : : 2N
%batch_normalization_14/AssignNewValue%batch_normalization_14/AssignNewValue2R
'batch_normalization_14/AssignNewValue_1'batch_normalization_14/AssignNewValue_12p
6batch_normalization_14/FusedBatchNormV3/ReadVariableOp6batch_normalization_14/FusedBatchNormV3/ReadVariableOp2t
8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_18batch_normalization_14/FusedBatchNormV3/ReadVariableOp_12N
%batch_normalization_14/ReadVariableOp%batch_normalization_14/ReadVariableOp2R
'batch_normalization_14/ReadVariableOp_1'batch_normalization_14/ReadVariableOp_1:W S
/
_output_shapes
:????????? 
 
_user_specified_nameargs_0
?
?
R__inference_batch_normalization_14_layer_call_and_return_conditional_losses_758270

inputs%
readvariableop_resource: '
readvariableop_1_resource: 6
(fusedbatchnormv3_readvariableop_resource: 8
*fusedbatchnormv3_readvariableop_1_resource: 
identity??FusedBatchNormV3/ReadVariableOp?!FusedBatchNormV3/ReadVariableOp_1?ReadVariableOp?ReadVariableOp_1t
ReadVariableOpReadVariableOpreadvariableop_resource*
_output_shapes
: *
dtype02
ReadVariableOpz
ReadVariableOp_1ReadVariableOpreadvariableop_1_resource*
_output_shapes
: *
dtype02
ReadVariableOp_1?
FusedBatchNormV3/ReadVariableOpReadVariableOp(fusedbatchnormv3_readvariableop_resource*
_output_shapes
: *
dtype02!
FusedBatchNormV3/ReadVariableOp?
!FusedBatchNormV3/ReadVariableOp_1ReadVariableOp*fusedbatchnormv3_readvariableop_1_resource*
_output_shapes
: *
dtype02#
!FusedBatchNormV3/ReadVariableOp_1?
FusedBatchNormV3FusedBatchNormV3inputsReadVariableOp:value:0ReadVariableOp_1:value:0'FusedBatchNormV3/ReadVariableOp:value:0)FusedBatchNormV3/ReadVariableOp_1:value:0*
T0*
U0*]
_output_shapesK
I:+??????????????????????????? : : : : :*
epsilon%o?:*
is_training( 2
FusedBatchNormV3?
IdentityIdentityFusedBatchNormV3:y:0 ^FusedBatchNormV3/ReadVariableOp"^FusedBatchNormV3/ReadVariableOp_1^ReadVariableOp^ReadVariableOp_1*
T0*A
_output_shapes/
-:+??????????????????????????? 2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*H
_input_shapes7
5:+??????????????????????????? : : : : 2B
FusedBatchNormV3/ReadVariableOpFusedBatchNormV3/ReadVariableOp2F
!FusedBatchNormV3/ReadVariableOp_1!FusedBatchNormV3/ReadVariableOp_12 
ReadVariableOpReadVariableOp2$
ReadVariableOp_1ReadVariableOp_1:i e
A
_output_shapes/
-:+??????????????????????????? 
 
_user_specified_nameinputs
?F
?
I__inference_sequential_20_layer_call_and_return_conditional_losses_758458

inputsB
(conv2d_20_conv2d_readvariableop_resource: 7
)conv2d_20_biasadd_readvariableop_resource: N
@module_wrapper_14_batch_normalization_14_readvariableop_resource: P
Bmodule_wrapper_14_batch_normalization_14_readvariableop_1_resource: _
Qmodule_wrapper_14_batch_normalization_14_fusedbatchnormv3_readvariableop_resource: a
Smodule_wrapper_14_batch_normalization_14_fusedbatchnormv3_readvariableop_1_resource: :
'dense_40_matmul_readvariableop_resource:	?*d6
(dense_40_biasadd_readvariableop_resource:d9
'dense_41_matmul_readvariableop_resource:d
6
(dense_41_biasadd_readvariableop_resource:

identity?? conv2d_20/BiasAdd/ReadVariableOp?conv2d_20/Conv2D/ReadVariableOp?dense_40/BiasAdd/ReadVariableOp?dense_40/MatMul/ReadVariableOp?dense_41/BiasAdd/ReadVariableOp?dense_41/MatMul/ReadVariableOp?7module_wrapper_14/batch_normalization_14/AssignNewValue?9module_wrapper_14/batch_normalization_14/AssignNewValue_1?Hmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp?Jmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1?7module_wrapper_14/batch_normalization_14/ReadVariableOp?9module_wrapper_14/batch_normalization_14/ReadVariableOp_1?
conv2d_20/Conv2D/ReadVariableOpReadVariableOp(conv2d_20_conv2d_readvariableop_resource*&
_output_shapes
: *
dtype02!
conv2d_20/Conv2D/ReadVariableOp?
conv2d_20/Conv2DConv2Dinputs'conv2d_20/Conv2D/ReadVariableOp:value:0*
T0*/
_output_shapes
:????????? *
paddingVALID*
strides
2
conv2d_20/Conv2D?
 conv2d_20/BiasAdd/ReadVariableOpReadVariableOp)conv2d_20_biasadd_readvariableop_resource*
_output_shapes
: *
dtype02"
 conv2d_20/BiasAdd/ReadVariableOp?
conv2d_20/BiasAddBiasAddconv2d_20/Conv2D:output:0(conv2d_20/BiasAdd/ReadVariableOp:value:0*
T0*/
_output_shapes
:????????? 2
conv2d_20/BiasAdd~
conv2d_20/ReluReluconv2d_20/BiasAdd:output:0*
T0*/
_output_shapes
:????????? 2
conv2d_20/Relu?
7module_wrapper_14/batch_normalization_14/ReadVariableOpReadVariableOp@module_wrapper_14_batch_normalization_14_readvariableop_resource*
_output_shapes
: *
dtype029
7module_wrapper_14/batch_normalization_14/ReadVariableOp?
9module_wrapper_14/batch_normalization_14/ReadVariableOp_1ReadVariableOpBmodule_wrapper_14_batch_normalization_14_readvariableop_1_resource*
_output_shapes
: *
dtype02;
9module_wrapper_14/batch_normalization_14/ReadVariableOp_1?
Hmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOpReadVariableOpQmodule_wrapper_14_batch_normalization_14_fusedbatchnormv3_readvariableop_resource*
_output_shapes
: *
dtype02J
Hmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp?
Jmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1ReadVariableOpSmodule_wrapper_14_batch_normalization_14_fusedbatchnormv3_readvariableop_1_resource*
_output_shapes
: *
dtype02L
Jmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1?
9module_wrapper_14/batch_normalization_14/FusedBatchNormV3FusedBatchNormV3conv2d_20/Relu:activations:0?module_wrapper_14/batch_normalization_14/ReadVariableOp:value:0Amodule_wrapper_14/batch_normalization_14/ReadVariableOp_1:value:0Pmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp:value:0Rmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1:value:0*
T0*
U0*K
_output_shapes9
7:????????? : : : : :*
epsilon%o?:*
exponential_avg_factor%
?#<2;
9module_wrapper_14/batch_normalization_14/FusedBatchNormV3?
7module_wrapper_14/batch_normalization_14/AssignNewValueAssignVariableOpQmodule_wrapper_14_batch_normalization_14_fusedbatchnormv3_readvariableop_resourceFmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3:batch_mean:0I^module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp*
_output_shapes
 *
dtype029
7module_wrapper_14/batch_normalization_14/AssignNewValue?
9module_wrapper_14/batch_normalization_14/AssignNewValue_1AssignVariableOpSmodule_wrapper_14_batch_normalization_14_fusedbatchnormv3_readvariableop_1_resourceJmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3:batch_variance:0K^module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1*
_output_shapes
 *
dtype02;
9module_wrapper_14/batch_normalization_14/AssignNewValue_1?
max_pooling2d_20/MaxPoolMaxPool=module_wrapper_14/batch_normalization_14/FusedBatchNormV3:y:0*/
_output_shapes
:????????? *
ksize
*
paddingVALID*
strides
2
max_pooling2d_20/MaxPoolu
flatten_20/ConstConst*
_output_shapes
:*
dtype0*
valueB"????   2
flatten_20/Const?
flatten_20/ReshapeReshape!max_pooling2d_20/MaxPool:output:0flatten_20/Const:output:0*
T0*(
_output_shapes
:??????????*2
flatten_20/Reshape?
dense_40/MatMul/ReadVariableOpReadVariableOp'dense_40_matmul_readvariableop_resource*
_output_shapes
:	?*d*
dtype02 
dense_40/MatMul/ReadVariableOp?
dense_40/MatMulMatMulflatten_20/Reshape:output:0&dense_40/MatMul/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????d2
dense_40/MatMul?
dense_40/BiasAdd/ReadVariableOpReadVariableOp(dense_40_biasadd_readvariableop_resource*
_output_shapes
:d*
dtype02!
dense_40/BiasAdd/ReadVariableOp?
dense_40/BiasAddBiasAdddense_40/MatMul:product:0'dense_40/BiasAdd/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????d2
dense_40/BiasAdds
dense_40/ReluReludense_40/BiasAdd:output:0*
T0*'
_output_shapes
:?????????d2
dense_40/Relu?
dense_41/MatMul/ReadVariableOpReadVariableOp'dense_41_matmul_readvariableop_resource*
_output_shapes

:d
*
dtype02 
dense_41/MatMul/ReadVariableOp?
dense_41/MatMulMatMuldense_40/Relu:activations:0&dense_41/MatMul/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????
2
dense_41/MatMul?
dense_41/BiasAdd/ReadVariableOpReadVariableOp(dense_41_biasadd_readvariableop_resource*
_output_shapes
:
*
dtype02!
dense_41/BiasAdd/ReadVariableOp?
dense_41/BiasAddBiasAdddense_41/MatMul:product:0'dense_41/BiasAdd/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????
2
dense_41/BiasAdd|
dense_41/SoftmaxSoftmaxdense_41/BiasAdd:output:0*
T0*'
_output_shapes
:?????????
2
dense_41/Softmax?
IdentityIdentitydense_41/Softmax:softmax:0!^conv2d_20/BiasAdd/ReadVariableOp ^conv2d_20/Conv2D/ReadVariableOp ^dense_40/BiasAdd/ReadVariableOp^dense_40/MatMul/ReadVariableOp ^dense_41/BiasAdd/ReadVariableOp^dense_41/MatMul/ReadVariableOp8^module_wrapper_14/batch_normalization_14/AssignNewValue:^module_wrapper_14/batch_normalization_14/AssignNewValue_1I^module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOpK^module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_18^module_wrapper_14/batch_normalization_14/ReadVariableOp:^module_wrapper_14/batch_normalization_14/ReadVariableOp_1*
T0*'
_output_shapes
:?????????
2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*B
_input_shapes1
/:?????????: : : : : : : : : : 2D
 conv2d_20/BiasAdd/ReadVariableOp conv2d_20/BiasAdd/ReadVariableOp2B
conv2d_20/Conv2D/ReadVariableOpconv2d_20/Conv2D/ReadVariableOp2B
dense_40/BiasAdd/ReadVariableOpdense_40/BiasAdd/ReadVariableOp2@
dense_40/MatMul/ReadVariableOpdense_40/MatMul/ReadVariableOp2B
dense_41/BiasAdd/ReadVariableOpdense_41/BiasAdd/ReadVariableOp2@
dense_41/MatMul/ReadVariableOpdense_41/MatMul/ReadVariableOp2r
7module_wrapper_14/batch_normalization_14/AssignNewValue7module_wrapper_14/batch_normalization_14/AssignNewValue2v
9module_wrapper_14/batch_normalization_14/AssignNewValue_19module_wrapper_14/batch_normalization_14/AssignNewValue_12?
Hmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOpHmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp2?
Jmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1Jmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_12r
7module_wrapper_14/batch_normalization_14/ReadVariableOp7module_wrapper_14/batch_normalization_14/ReadVariableOp2v
9module_wrapper_14/batch_normalization_14/ReadVariableOp_19module_wrapper_14/batch_normalization_14/ReadVariableOp_1:W S
/
_output_shapes
:?????????
 
_user_specified_nameinputs
?
?
M__inference_module_wrapper_14_layer_call_and_return_conditional_losses_758035

args_0<
.batch_normalization_14_readvariableop_resource: >
0batch_normalization_14_readvariableop_1_resource: M
?batch_normalization_14_fusedbatchnormv3_readvariableop_resource: O
Abatch_normalization_14_fusedbatchnormv3_readvariableop_1_resource: 
identity??%batch_normalization_14/AssignNewValue?'batch_normalization_14/AssignNewValue_1?6batch_normalization_14/FusedBatchNormV3/ReadVariableOp?8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1?%batch_normalization_14/ReadVariableOp?'batch_normalization_14/ReadVariableOp_1?
%batch_normalization_14/ReadVariableOpReadVariableOp.batch_normalization_14_readvariableop_resource*
_output_shapes
: *
dtype02'
%batch_normalization_14/ReadVariableOp?
'batch_normalization_14/ReadVariableOp_1ReadVariableOp0batch_normalization_14_readvariableop_1_resource*
_output_shapes
: *
dtype02)
'batch_normalization_14/ReadVariableOp_1?
6batch_normalization_14/FusedBatchNormV3/ReadVariableOpReadVariableOp?batch_normalization_14_fusedbatchnormv3_readvariableop_resource*
_output_shapes
: *
dtype028
6batch_normalization_14/FusedBatchNormV3/ReadVariableOp?
8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1ReadVariableOpAbatch_normalization_14_fusedbatchnormv3_readvariableop_1_resource*
_output_shapes
: *
dtype02:
8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1?
'batch_normalization_14/FusedBatchNormV3FusedBatchNormV3args_0-batch_normalization_14/ReadVariableOp:value:0/batch_normalization_14/ReadVariableOp_1:value:0>batch_normalization_14/FusedBatchNormV3/ReadVariableOp:value:0@batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1:value:0*
T0*
U0*K
_output_shapes9
7:????????? : : : : :*
epsilon%o?:*
exponential_avg_factor%
?#<2)
'batch_normalization_14/FusedBatchNormV3?
%batch_normalization_14/AssignNewValueAssignVariableOp?batch_normalization_14_fusedbatchnormv3_readvariableop_resource4batch_normalization_14/FusedBatchNormV3:batch_mean:07^batch_normalization_14/FusedBatchNormV3/ReadVariableOp*
_output_shapes
 *
dtype02'
%batch_normalization_14/AssignNewValue?
'batch_normalization_14/AssignNewValue_1AssignVariableOpAbatch_normalization_14_fusedbatchnormv3_readvariableop_1_resource8batch_normalization_14/FusedBatchNormV3:batch_variance:09^batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1*
_output_shapes
 *
dtype02)
'batch_normalization_14/AssignNewValue_1?
IdentityIdentity+batch_normalization_14/FusedBatchNormV3:y:0&^batch_normalization_14/AssignNewValue(^batch_normalization_14/AssignNewValue_17^batch_normalization_14/FusedBatchNormV3/ReadVariableOp9^batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1&^batch_normalization_14/ReadVariableOp(^batch_normalization_14/ReadVariableOp_1*
T0*/
_output_shapes
:????????? 2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*6
_input_shapes%
#:????????? : : : : 2N
%batch_normalization_14/AssignNewValue%batch_normalization_14/AssignNewValue2R
'batch_normalization_14/AssignNewValue_1'batch_normalization_14/AssignNewValue_12p
6batch_normalization_14/FusedBatchNormV3/ReadVariableOp6batch_normalization_14/FusedBatchNormV3/ReadVariableOp2t
8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_18batch_normalization_14/FusedBatchNormV3/ReadVariableOp_12N
%batch_normalization_14/ReadVariableOp%batch_normalization_14/ReadVariableOp2R
'batch_normalization_14/ReadVariableOp_1'batch_normalization_14/ReadVariableOp_1:W S
/
_output_shapes
:????????? 
 
_user_specified_nameargs_0
?

?
.__inference_sequential_20_layer_call_fn_758161
conv2d_20_input!
unknown: 
	unknown_0: 
	unknown_1: 
	unknown_2: 
	unknown_3: 
	unknown_4: 
	unknown_5:	?*d
	unknown_6:d
	unknown_7:d

	unknown_8:

identity??StatefulPartitionedCall?
StatefulPartitionedCallStatefulPartitionedCallconv2d_20_inputunknown	unknown_0	unknown_1	unknown_2	unknown_3	unknown_4	unknown_5	unknown_6	unknown_7	unknown_8*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????
**
_read_only_resource_inputs

	
*-
config_proto

CPU

GPU 2J 8? *R
fMRK
I__inference_sequential_20_layer_call_and_return_conditional_losses_7581132
StatefulPartitionedCall?
IdentityIdentity StatefulPartitionedCall:output:0^StatefulPartitionedCall*
T0*'
_output_shapes
:?????????
2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*B
_input_shapes1
/:?????????: : : : : : : : : : 22
StatefulPartitionedCallStatefulPartitionedCall:` \
/
_output_shapes
:?????????
)
_user_specified_nameconv2d_20_input
?
?
R__inference_batch_normalization_14_layer_call_and_return_conditional_losses_758677

inputs%
readvariableop_resource: '
readvariableop_1_resource: 6
(fusedbatchnormv3_readvariableop_resource: 8
*fusedbatchnormv3_readvariableop_1_resource: 
identity??AssignNewValue?AssignNewValue_1?FusedBatchNormV3/ReadVariableOp?!FusedBatchNormV3/ReadVariableOp_1?ReadVariableOp?ReadVariableOp_1t
ReadVariableOpReadVariableOpreadvariableop_resource*
_output_shapes
: *
dtype02
ReadVariableOpz
ReadVariableOp_1ReadVariableOpreadvariableop_1_resource*
_output_shapes
: *
dtype02
ReadVariableOp_1?
FusedBatchNormV3/ReadVariableOpReadVariableOp(fusedbatchnormv3_readvariableop_resource*
_output_shapes
: *
dtype02!
FusedBatchNormV3/ReadVariableOp?
!FusedBatchNormV3/ReadVariableOp_1ReadVariableOp*fusedbatchnormv3_readvariableop_1_resource*
_output_shapes
: *
dtype02#
!FusedBatchNormV3/ReadVariableOp_1?
FusedBatchNormV3FusedBatchNormV3inputsReadVariableOp:value:0ReadVariableOp_1:value:0'FusedBatchNormV3/ReadVariableOp:value:0)FusedBatchNormV3/ReadVariableOp_1:value:0*
T0*
U0*]
_output_shapesK
I:+??????????????????????????? : : : : :*
epsilon%o?:*
exponential_avg_factor%
?#<2
FusedBatchNormV3?
AssignNewValueAssignVariableOp(fusedbatchnormv3_readvariableop_resourceFusedBatchNormV3:batch_mean:0 ^FusedBatchNormV3/ReadVariableOp*
_output_shapes
 *
dtype02
AssignNewValue?
AssignNewValue_1AssignVariableOp*fusedbatchnormv3_readvariableop_1_resource!FusedBatchNormV3:batch_variance:0"^FusedBatchNormV3/ReadVariableOp_1*
_output_shapes
 *
dtype02
AssignNewValue_1?
IdentityIdentityFusedBatchNormV3:y:0^AssignNewValue^AssignNewValue_1 ^FusedBatchNormV3/ReadVariableOp"^FusedBatchNormV3/ReadVariableOp_1^ReadVariableOp^ReadVariableOp_1*
T0*A
_output_shapes/
-:+??????????????????????????? 2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*H
_input_shapes7
5:+??????????????????????????? : : : : 2 
AssignNewValueAssignNewValue2$
AssignNewValue_1AssignNewValue_12B
FusedBatchNormV3/ReadVariableOpFusedBatchNormV3/ReadVariableOp2F
!FusedBatchNormV3/ReadVariableOp_1!FusedBatchNormV3/ReadVariableOp_12 
ReadVariableOpReadVariableOp2$
ReadVariableOp_1ReadVariableOp_1:i e
A
_output_shapes/
-:+??????????????????????????? 
 
_user_specified_nameinputs
?

?
.__inference_sequential_20_layer_call_fn_757975
conv2d_20_input!
unknown: 
	unknown_0: 
	unknown_1: 
	unknown_2: 
	unknown_3: 
	unknown_4: 
	unknown_5:	?*d
	unknown_6:d
	unknown_7:d

	unknown_8:

identity??StatefulPartitionedCall?
StatefulPartitionedCallStatefulPartitionedCallconv2d_20_inputunknown	unknown_0	unknown_1	unknown_2	unknown_3	unknown_4	unknown_5	unknown_6	unknown_7	unknown_8*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????
*,
_read_only_resource_inputs

	
*-
config_proto

CPU

GPU 2J 8? *R
fMRK
I__inference_sequential_20_layer_call_and_return_conditional_losses_7579522
StatefulPartitionedCall?
IdentityIdentity StatefulPartitionedCall:output:0^StatefulPartitionedCall*
T0*'
_output_shapes
:?????????
2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*B
_input_shapes1
/:?????????: : : : : : : : : : 22
StatefulPartitionedCallStatefulPartitionedCall:` \
/
_output_shapes
:?????????
)
_user_specified_nameconv2d_20_input
?
?
*__inference_conv2d_20_layer_call_fn_758528

inputs!
unknown: 
	unknown_0: 
identity??StatefulPartitionedCall?
StatefulPartitionedCallStatefulPartitionedCallinputsunknown	unknown_0*
Tin
2*
Tout
2*
_collective_manager_ids
 */
_output_shapes
:????????? *$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *N
fIRG
E__inference_conv2d_20_layer_call_and_return_conditional_losses_7578742
StatefulPartitionedCall?
IdentityIdentity StatefulPartitionedCall:output:0^StatefulPartitionedCall*
T0*/
_output_shapes
:????????? 2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*2
_input_shapes!
:?????????: : 22
StatefulPartitionedCallStatefulPartitionedCall:W S
/
_output_shapes
:?????????
 
_user_specified_nameinputs
??
?	
"__inference__traced_restore_758820
file_prefix;
!assignvariableop_conv2d_20_kernel: /
!assignvariableop_1_conv2d_20_bias: 5
"assignvariableop_2_dense_40_kernel:	?*d.
 assignvariableop_3_dense_40_bias:d4
"assignvariableop_4_dense_41_kernel:d
.
 assignvariableop_5_dense_41_bias:
O
Aassignvariableop_6_module_wrapper_14_batch_normalization_14_gamma: N
@assignvariableop_7_module_wrapper_14_batch_normalization_14_beta: U
Gassignvariableop_8_module_wrapper_14_batch_normalization_14_moving_mean: Y
Kassignvariableop_9_module_wrapper_14_batch_normalization_14_moving_variance: #
assignvariableop_10_total: #
assignvariableop_11_count: %
assignvariableop_12_total_1: %
assignvariableop_13_count_1: 
identity_15??AssignVariableOp?AssignVariableOp_1?AssignVariableOp_10?AssignVariableOp_11?AssignVariableOp_12?AssignVariableOp_13?AssignVariableOp_2?AssignVariableOp_3?AssignVariableOp_4?AssignVariableOp_5?AssignVariableOp_6?AssignVariableOp_7?AssignVariableOp_8?AssignVariableOp_9?
RestoreV2/tensor_namesConst"/device:CPU:0*
_output_shapes
:*
dtype0*?
value?B?B6layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUEB4layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUEB6layer_with_weights-2/kernel/.ATTRIBUTES/VARIABLE_VALUEB4layer_with_weights-2/bias/.ATTRIBUTES/VARIABLE_VALUEB6layer_with_weights-3/kernel/.ATTRIBUTES/VARIABLE_VALUEB4layer_with_weights-3/bias/.ATTRIBUTES/VARIABLE_VALUEB&variables/2/.ATTRIBUTES/VARIABLE_VALUEB&variables/3/.ATTRIBUTES/VARIABLE_VALUEB&variables/4/.ATTRIBUTES/VARIABLE_VALUEB&variables/5/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/0/total/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/0/count/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/1/total/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/1/count/.ATTRIBUTES/VARIABLE_VALUEB_CHECKPOINTABLE_OBJECT_GRAPH2
RestoreV2/tensor_names?
RestoreV2/shape_and_slicesConst"/device:CPU:0*
_output_shapes
:*
dtype0*1
value(B&B B B B B B B B B B B B B B B 2
RestoreV2/shape_and_slices?
	RestoreV2	RestoreV2file_prefixRestoreV2/tensor_names:output:0#RestoreV2/shape_and_slices:output:0"/device:CPU:0*P
_output_shapes>
<:::::::::::::::*
dtypes
22
	RestoreV2g
IdentityIdentityRestoreV2:tensors:0"/device:CPU:0*
T0*
_output_shapes
:2

Identity?
AssignVariableOpAssignVariableOp!assignvariableop_conv2d_20_kernelIdentity:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOpk

Identity_1IdentityRestoreV2:tensors:1"/device:CPU:0*
T0*
_output_shapes
:2

Identity_1?
AssignVariableOp_1AssignVariableOp!assignvariableop_1_conv2d_20_biasIdentity_1:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_1k

Identity_2IdentityRestoreV2:tensors:2"/device:CPU:0*
T0*
_output_shapes
:2

Identity_2?
AssignVariableOp_2AssignVariableOp"assignvariableop_2_dense_40_kernelIdentity_2:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_2k

Identity_3IdentityRestoreV2:tensors:3"/device:CPU:0*
T0*
_output_shapes
:2

Identity_3?
AssignVariableOp_3AssignVariableOp assignvariableop_3_dense_40_biasIdentity_3:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_3k

Identity_4IdentityRestoreV2:tensors:4"/device:CPU:0*
T0*
_output_shapes
:2

Identity_4?
AssignVariableOp_4AssignVariableOp"assignvariableop_4_dense_41_kernelIdentity_4:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_4k

Identity_5IdentityRestoreV2:tensors:5"/device:CPU:0*
T0*
_output_shapes
:2

Identity_5?
AssignVariableOp_5AssignVariableOp assignvariableop_5_dense_41_biasIdentity_5:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_5k

Identity_6IdentityRestoreV2:tensors:6"/device:CPU:0*
T0*
_output_shapes
:2

Identity_6?
AssignVariableOp_6AssignVariableOpAassignvariableop_6_module_wrapper_14_batch_normalization_14_gammaIdentity_6:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_6k

Identity_7IdentityRestoreV2:tensors:7"/device:CPU:0*
T0*
_output_shapes
:2

Identity_7?
AssignVariableOp_7AssignVariableOp@assignvariableop_7_module_wrapper_14_batch_normalization_14_betaIdentity_7:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_7k

Identity_8IdentityRestoreV2:tensors:8"/device:CPU:0*
T0*
_output_shapes
:2

Identity_8?
AssignVariableOp_8AssignVariableOpGassignvariableop_8_module_wrapper_14_batch_normalization_14_moving_meanIdentity_8:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_8k

Identity_9IdentityRestoreV2:tensors:9"/device:CPU:0*
T0*
_output_shapes
:2

Identity_9?
AssignVariableOp_9AssignVariableOpKassignvariableop_9_module_wrapper_14_batch_normalization_14_moving_varianceIdentity_9:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_9n
Identity_10IdentityRestoreV2:tensors:10"/device:CPU:0*
T0*
_output_shapes
:2
Identity_10?
AssignVariableOp_10AssignVariableOpassignvariableop_10_totalIdentity_10:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_10n
Identity_11IdentityRestoreV2:tensors:11"/device:CPU:0*
T0*
_output_shapes
:2
Identity_11?
AssignVariableOp_11AssignVariableOpassignvariableop_11_countIdentity_11:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_11n
Identity_12IdentityRestoreV2:tensors:12"/device:CPU:0*
T0*
_output_shapes
:2
Identity_12?
AssignVariableOp_12AssignVariableOpassignvariableop_12_total_1Identity_12:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_12n
Identity_13IdentityRestoreV2:tensors:13"/device:CPU:0*
T0*
_output_shapes
:2
Identity_13?
AssignVariableOp_13AssignVariableOpassignvariableop_13_count_1Identity_13:output:0"/device:CPU:0*
_output_shapes
 *
dtype02
AssignVariableOp_139
NoOpNoOp"/device:CPU:0*
_output_shapes
 2
NoOp?
Identity_14Identityfile_prefix^AssignVariableOp^AssignVariableOp_1^AssignVariableOp_10^AssignVariableOp_11^AssignVariableOp_12^AssignVariableOp_13^AssignVariableOp_2^AssignVariableOp_3^AssignVariableOp_4^AssignVariableOp_5^AssignVariableOp_6^AssignVariableOp_7^AssignVariableOp_8^AssignVariableOp_9^NoOp"/device:CPU:0*
T0*
_output_shapes
: 2
Identity_14?
Identity_15IdentityIdentity_14:output:0^AssignVariableOp^AssignVariableOp_1^AssignVariableOp_10^AssignVariableOp_11^AssignVariableOp_12^AssignVariableOp_13^AssignVariableOp_2^AssignVariableOp_3^AssignVariableOp_4^AssignVariableOp_5^AssignVariableOp_6^AssignVariableOp_7^AssignVariableOp_8^AssignVariableOp_9*
T0*
_output_shapes
: 2
Identity_15"#
identity_15Identity_15:output:0*1
_input_shapes 
: : : : : : : : : : : : : : : 2$
AssignVariableOpAssignVariableOp2(
AssignVariableOp_1AssignVariableOp_12*
AssignVariableOp_10AssignVariableOp_102*
AssignVariableOp_11AssignVariableOp_112*
AssignVariableOp_12AssignVariableOp_122*
AssignVariableOp_13AssignVariableOp_132(
AssignVariableOp_2AssignVariableOp_22(
AssignVariableOp_3AssignVariableOp_32(
AssignVariableOp_4AssignVariableOp_42(
AssignVariableOp_5AssignVariableOp_52(
AssignVariableOp_6AssignVariableOp_62(
AssignVariableOp_7AssignVariableOp_72(
AssignVariableOp_8AssignVariableOp_82(
AssignVariableOp_9AssignVariableOp_9:C ?

_output_shapes
: 
%
_user_specified_namefile_prefix
?

?
D__inference_dense_40_layer_call_and_return_conditional_losses_758612

inputs1
matmul_readvariableop_resource:	?*d-
biasadd_readvariableop_resource:d
identity??BiasAdd/ReadVariableOp?MatMul/ReadVariableOp?
MatMul/ReadVariableOpReadVariableOpmatmul_readvariableop_resource*
_output_shapes
:	?*d*
dtype02
MatMul/ReadVariableOps
MatMulMatMulinputsMatMul/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????d2
MatMul?
BiasAdd/ReadVariableOpReadVariableOpbiasadd_readvariableop_resource*
_output_shapes
:d*
dtype02
BiasAdd/ReadVariableOp?
BiasAddBiasAddMatMul:product:0BiasAdd/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????d2	
BiasAddX
ReluReluBiasAdd:output:0*
T0*'
_output_shapes
:?????????d2
Relu?
IdentityIdentityRelu:activations:0^BiasAdd/ReadVariableOp^MatMul/ReadVariableOp*
T0*'
_output_shapes
:?????????d2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*+
_input_shapes
:??????????*: : 20
BiasAdd/ReadVariableOpBiasAdd/ReadVariableOp2.
MatMul/ReadVariableOpMatMul/ReadVariableOp:P L
(
_output_shapes
:??????????*
 
_user_specified_nameinputs
?	
?
$__inference_signature_wrapper_758248
conv2d_20_input!
unknown: 
	unknown_0: 
	unknown_1: 
	unknown_2: 
	unknown_3: 
	unknown_4: 
	unknown_5:	?*d
	unknown_6:d
	unknown_7:d

	unknown_8:

identity??StatefulPartitionedCall?
StatefulPartitionedCallStatefulPartitionedCallconv2d_20_inputunknown	unknown_0	unknown_1	unknown_2	unknown_3	unknown_4	unknown_5	unknown_6	unknown_7	unknown_8*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????
*,
_read_only_resource_inputs

	
*-
config_proto

CPU

GPU 2J 8? **
f%R#
!__inference__wrapped_model_7578442
StatefulPartitionedCall?
IdentityIdentity StatefulPartitionedCall:output:0^StatefulPartitionedCall*
T0*'
_output_shapes
:?????????
2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*B
_input_shapes1
/:?????????: : : : : : : : : : 22
StatefulPartitionedCallStatefulPartitionedCall:` \
/
_output_shapes
:?????????
)
_user_specified_nameconv2d_20_input
?

?
D__inference_dense_40_layer_call_and_return_conditional_losses_757928

inputs1
matmul_readvariableop_resource:	?*d-
biasadd_readvariableop_resource:d
identity??BiasAdd/ReadVariableOp?MatMul/ReadVariableOp?
MatMul/ReadVariableOpReadVariableOpmatmul_readvariableop_resource*
_output_shapes
:	?*d*
dtype02
MatMul/ReadVariableOps
MatMulMatMulinputsMatMul/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????d2
MatMul?
BiasAdd/ReadVariableOpReadVariableOpbiasadd_readvariableop_resource*
_output_shapes
:d*
dtype02
BiasAdd/ReadVariableOp?
BiasAddBiasAddMatMul:product:0BiasAdd/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????d2	
BiasAddX
ReluReluBiasAdd:output:0*
T0*'
_output_shapes
:?????????d2
Relu?
IdentityIdentityRelu:activations:0^BiasAdd/ReadVariableOp^MatMul/ReadVariableOp*
T0*'
_output_shapes
:?????????d2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*+
_input_shapes
:??????????*: : 20
BiasAdd/ReadVariableOpBiasAdd/ReadVariableOp2.
MatMul/ReadVariableOpMatMul/ReadVariableOp:P L
(
_output_shapes
:??????????*
 
_user_specified_nameinputs
?
?
E__inference_conv2d_20_layer_call_and_return_conditional_losses_757874

inputs8
conv2d_readvariableop_resource: -
biasadd_readvariableop_resource: 
identity??BiasAdd/ReadVariableOp?Conv2D/ReadVariableOp?
Conv2D/ReadVariableOpReadVariableOpconv2d_readvariableop_resource*&
_output_shapes
: *
dtype02
Conv2D/ReadVariableOp?
Conv2DConv2DinputsConv2D/ReadVariableOp:value:0*
T0*/
_output_shapes
:????????? *
paddingVALID*
strides
2
Conv2D?
BiasAdd/ReadVariableOpReadVariableOpbiasadd_readvariableop_resource*
_output_shapes
: *
dtype02
BiasAdd/ReadVariableOp?
BiasAddBiasAddConv2D:output:0BiasAdd/ReadVariableOp:value:0*
T0*/
_output_shapes
:????????? 2	
BiasAdd`
ReluReluBiasAdd:output:0*
T0*/
_output_shapes
:????????? 2
Relu?
IdentityIdentityRelu:activations:0^BiasAdd/ReadVariableOp^Conv2D/ReadVariableOp*
T0*/
_output_shapes
:????????? 2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*2
_input_shapes!
:?????????: : 20
BiasAdd/ReadVariableOpBiasAdd/ReadVariableOp2.
Conv2D/ReadVariableOpConv2D/ReadVariableOp:W S
/
_output_shapes
:?????????
 
_user_specified_nameinputs
?
?
M__inference_module_wrapper_14_layer_call_and_return_conditional_losses_758546

args_0<
.batch_normalization_14_readvariableop_resource: >
0batch_normalization_14_readvariableop_1_resource: M
?batch_normalization_14_fusedbatchnormv3_readvariableop_resource: O
Abatch_normalization_14_fusedbatchnormv3_readvariableop_1_resource: 
identity??6batch_normalization_14/FusedBatchNormV3/ReadVariableOp?8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1?%batch_normalization_14/ReadVariableOp?'batch_normalization_14/ReadVariableOp_1?
%batch_normalization_14/ReadVariableOpReadVariableOp.batch_normalization_14_readvariableop_resource*
_output_shapes
: *
dtype02'
%batch_normalization_14/ReadVariableOp?
'batch_normalization_14/ReadVariableOp_1ReadVariableOp0batch_normalization_14_readvariableop_1_resource*
_output_shapes
: *
dtype02)
'batch_normalization_14/ReadVariableOp_1?
6batch_normalization_14/FusedBatchNormV3/ReadVariableOpReadVariableOp?batch_normalization_14_fusedbatchnormv3_readvariableop_resource*
_output_shapes
: *
dtype028
6batch_normalization_14/FusedBatchNormV3/ReadVariableOp?
8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1ReadVariableOpAbatch_normalization_14_fusedbatchnormv3_readvariableop_1_resource*
_output_shapes
: *
dtype02:
8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1?
'batch_normalization_14/FusedBatchNormV3FusedBatchNormV3args_0-batch_normalization_14/ReadVariableOp:value:0/batch_normalization_14/ReadVariableOp_1:value:0>batch_normalization_14/FusedBatchNormV3/ReadVariableOp:value:0@batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1:value:0*
T0*
U0*K
_output_shapes9
7:????????? : : : : :*
epsilon%o?:*
is_training( 2)
'batch_normalization_14/FusedBatchNormV3?
IdentityIdentity+batch_normalization_14/FusedBatchNormV3:y:07^batch_normalization_14/FusedBatchNormV3/ReadVariableOp9^batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1&^batch_normalization_14/ReadVariableOp(^batch_normalization_14/ReadVariableOp_1*
T0*/
_output_shapes
:????????? 2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*6
_input_shapes%
#:????????? : : : : 2p
6batch_normalization_14/FusedBatchNormV3/ReadVariableOp6batch_normalization_14/FusedBatchNormV3/ReadVariableOp2t
8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_18batch_normalization_14/FusedBatchNormV3/ReadVariableOp_12N
%batch_normalization_14/ReadVariableOp%batch_normalization_14/ReadVariableOp2R
'batch_normalization_14/ReadVariableOp_1'batch_normalization_14/ReadVariableOp_1:W S
/
_output_shapes
:????????? 
 
_user_specified_nameargs_0
?
?
I__inference_sequential_20_layer_call_and_return_conditional_losses_758113

inputs*
conv2d_20_758086: 
conv2d_20_758088: &
module_wrapper_14_758091: &
module_wrapper_14_758093: &
module_wrapper_14_758095: &
module_wrapper_14_758097: "
dense_40_758102:	?*d
dense_40_758104:d!
dense_41_758107:d

dense_41_758109:

identity??!conv2d_20/StatefulPartitionedCall? dense_40/StatefulPartitionedCall? dense_41/StatefulPartitionedCall?)module_wrapper_14/StatefulPartitionedCall?
!conv2d_20/StatefulPartitionedCallStatefulPartitionedCallinputsconv2d_20_758086conv2d_20_758088*
Tin
2*
Tout
2*
_collective_manager_ids
 */
_output_shapes
:????????? *$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *N
fIRG
E__inference_conv2d_20_layer_call_and_return_conditional_losses_7578742#
!conv2d_20/StatefulPartitionedCall?
)module_wrapper_14/StatefulPartitionedCallStatefulPartitionedCall*conv2d_20/StatefulPartitionedCall:output:0module_wrapper_14_758091module_wrapper_14_758093module_wrapper_14_758095module_wrapper_14_758097*
Tin	
2*
Tout
2*
_collective_manager_ids
 */
_output_shapes
:????????? *$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *V
fQRO
M__inference_module_wrapper_14_layer_call_and_return_conditional_losses_7580352+
)module_wrapper_14/StatefulPartitionedCall?
 max_pooling2d_20/PartitionedCallPartitionedCall2module_wrapper_14/StatefulPartitionedCall:output:0*
Tin
2*
Tout
2*
_collective_manager_ids
 */
_output_shapes
:????????? * 
_read_only_resource_inputs
 *-
config_proto

CPU

GPU 2J 8? *U
fPRN
L__inference_max_pooling2d_20_layer_call_and_return_conditional_losses_7578502"
 max_pooling2d_20/PartitionedCall?
flatten_20/PartitionedCallPartitionedCall)max_pooling2d_20/PartitionedCall:output:0*
Tin
2*
Tout
2*
_collective_manager_ids
 *(
_output_shapes
:??????????** 
_read_only_resource_inputs
 *-
config_proto

CPU

GPU 2J 8? *O
fJRH
F__inference_flatten_20_layer_call_and_return_conditional_losses_7579152
flatten_20/PartitionedCall?
 dense_40/StatefulPartitionedCallStatefulPartitionedCall#flatten_20/PartitionedCall:output:0dense_40_758102dense_40_758104*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????d*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *M
fHRF
D__inference_dense_40_layer_call_and_return_conditional_losses_7579282"
 dense_40/StatefulPartitionedCall?
 dense_41/StatefulPartitionedCallStatefulPartitionedCall)dense_40/StatefulPartitionedCall:output:0dense_41_758107dense_41_758109*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????
*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *M
fHRF
D__inference_dense_41_layer_call_and_return_conditional_losses_7579452"
 dense_41/StatefulPartitionedCall?
IdentityIdentity)dense_41/StatefulPartitionedCall:output:0"^conv2d_20/StatefulPartitionedCall!^dense_40/StatefulPartitionedCall!^dense_41/StatefulPartitionedCall*^module_wrapper_14/StatefulPartitionedCall*
T0*'
_output_shapes
:?????????
2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*B
_input_shapes1
/:?????????: : : : : : : : : : 2F
!conv2d_20/StatefulPartitionedCall!conv2d_20/StatefulPartitionedCall2D
 dense_40/StatefulPartitionedCall dense_40/StatefulPartitionedCall2D
 dense_41/StatefulPartitionedCall dense_41/StatefulPartitionedCall2V
)module_wrapper_14/StatefulPartitionedCall)module_wrapper_14/StatefulPartitionedCall:W S
/
_output_shapes
:?????????
 
_user_specified_nameinputs
?
M
1__inference_max_pooling2d_20_layer_call_fn_757856

inputs
identity?
PartitionedCallPartitionedCallinputs*
Tin
2*
Tout
2*
_collective_manager_ids
 *J
_output_shapes8
6:4????????????????????????????????????* 
_read_only_resource_inputs
 *-
config_proto

CPU

GPU 2J 8? *U
fPRN
L__inference_max_pooling2d_20_layer_call_and_return_conditional_losses_7578502
PartitionedCall?
IdentityIdentityPartitionedCall:output:0*
T0*J
_output_shapes8
6:4????????????????????????????????????2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*I
_input_shapes8
6:4????????????????????????????????????:r n
J
_output_shapes8
6:4????????????????????????????????????
 
_user_specified_nameinputs
?
?
I__inference_sequential_20_layer_call_and_return_conditional_losses_757952

inputs*
conv2d_20_757875: 
conv2d_20_757877: &
module_wrapper_14_757899: &
module_wrapper_14_757901: &
module_wrapper_14_757903: &
module_wrapper_14_757905: "
dense_40_757929:	?*d
dense_40_757931:d!
dense_41_757946:d

dense_41_757948:

identity??!conv2d_20/StatefulPartitionedCall? dense_40/StatefulPartitionedCall? dense_41/StatefulPartitionedCall?)module_wrapper_14/StatefulPartitionedCall?
!conv2d_20/StatefulPartitionedCallStatefulPartitionedCallinputsconv2d_20_757875conv2d_20_757877*
Tin
2*
Tout
2*
_collective_manager_ids
 */
_output_shapes
:????????? *$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *N
fIRG
E__inference_conv2d_20_layer_call_and_return_conditional_losses_7578742#
!conv2d_20/StatefulPartitionedCall?
)module_wrapper_14/StatefulPartitionedCallStatefulPartitionedCall*conv2d_20/StatefulPartitionedCall:output:0module_wrapper_14_757899module_wrapper_14_757901module_wrapper_14_757903module_wrapper_14_757905*
Tin	
2*
Tout
2*
_collective_manager_ids
 */
_output_shapes
:????????? *&
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *V
fQRO
M__inference_module_wrapper_14_layer_call_and_return_conditional_losses_7578982+
)module_wrapper_14/StatefulPartitionedCall?
 max_pooling2d_20/PartitionedCallPartitionedCall2module_wrapper_14/StatefulPartitionedCall:output:0*
Tin
2*
Tout
2*
_collective_manager_ids
 */
_output_shapes
:????????? * 
_read_only_resource_inputs
 *-
config_proto

CPU

GPU 2J 8? *U
fPRN
L__inference_max_pooling2d_20_layer_call_and_return_conditional_losses_7578502"
 max_pooling2d_20/PartitionedCall?
flatten_20/PartitionedCallPartitionedCall)max_pooling2d_20/PartitionedCall:output:0*
Tin
2*
Tout
2*
_collective_manager_ids
 *(
_output_shapes
:??????????** 
_read_only_resource_inputs
 *-
config_proto

CPU

GPU 2J 8? *O
fJRH
F__inference_flatten_20_layer_call_and_return_conditional_losses_7579152
flatten_20/PartitionedCall?
 dense_40/StatefulPartitionedCallStatefulPartitionedCall#flatten_20/PartitionedCall:output:0dense_40_757929dense_40_757931*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????d*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *M
fHRF
D__inference_dense_40_layer_call_and_return_conditional_losses_7579282"
 dense_40/StatefulPartitionedCall?
 dense_41/StatefulPartitionedCallStatefulPartitionedCall)dense_40/StatefulPartitionedCall:output:0dense_41_757946dense_41_757948*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????
*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *M
fHRF
D__inference_dense_41_layer_call_and_return_conditional_losses_7579452"
 dense_41/StatefulPartitionedCall?
IdentityIdentity)dense_41/StatefulPartitionedCall:output:0"^conv2d_20/StatefulPartitionedCall!^dense_40/StatefulPartitionedCall!^dense_41/StatefulPartitionedCall*^module_wrapper_14/StatefulPartitionedCall*
T0*'
_output_shapes
:?????????
2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*B
_input_shapes1
/:?????????: : : : : : : : : : 2F
!conv2d_20/StatefulPartitionedCall!conv2d_20/StatefulPartitionedCall2D
 dense_40/StatefulPartitionedCall dense_40/StatefulPartitionedCall2D
 dense_41/StatefulPartitionedCall dense_41/StatefulPartitionedCall2V
)module_wrapper_14/StatefulPartitionedCall)module_wrapper_14/StatefulPartitionedCall:W S
/
_output_shapes
:?????????
 
_user_specified_nameinputs
?
b
F__inference_flatten_20_layer_call_and_return_conditional_losses_758596

inputs
identity_
ConstConst*
_output_shapes
:*
dtype0*
valueB"????   2
Consth
ReshapeReshapeinputsConst:output:0*
T0*(
_output_shapes
:??????????*2	
Reshapee
IdentityIdentityReshape:output:0*
T0*(
_output_shapes
:??????????*2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*.
_input_shapes
:????????? :W S
/
_output_shapes
:????????? 
 
_user_specified_nameinputs
?

?
D__inference_dense_41_layer_call_and_return_conditional_losses_758632

inputs0
matmul_readvariableop_resource:d
-
biasadd_readvariableop_resource:

identity??BiasAdd/ReadVariableOp?MatMul/ReadVariableOp?
MatMul/ReadVariableOpReadVariableOpmatmul_readvariableop_resource*
_output_shapes

:d
*
dtype02
MatMul/ReadVariableOps
MatMulMatMulinputsMatMul/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????
2
MatMul?
BiasAdd/ReadVariableOpReadVariableOpbiasadd_readvariableop_resource*
_output_shapes
:
*
dtype02
BiasAdd/ReadVariableOp?
BiasAddBiasAddMatMul:product:0BiasAdd/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????
2	
BiasAdda
SoftmaxSoftmaxBiasAdd:output:0*
T0*'
_output_shapes
:?????????
2	
Softmax?
IdentityIdentitySoftmax:softmax:0^BiasAdd/ReadVariableOp^MatMul/ReadVariableOp*
T0*'
_output_shapes
:?????????
2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime**
_input_shapes
:?????????d: : 20
BiasAdd/ReadVariableOpBiasAdd/ReadVariableOp2.
MatMul/ReadVariableOpMatMul/ReadVariableOp:O K
'
_output_shapes
:?????????d
 
_user_specified_nameinputs
?

?
.__inference_sequential_20_layer_call_fn_758483

inputs!
unknown: 
	unknown_0: 
	unknown_1: 
	unknown_2: 
	unknown_3: 
	unknown_4: 
	unknown_5:	?*d
	unknown_6:d
	unknown_7:d

	unknown_8:

identity??StatefulPartitionedCall?
StatefulPartitionedCallStatefulPartitionedCallinputsunknown	unknown_0	unknown_1	unknown_2	unknown_3	unknown_4	unknown_5	unknown_6	unknown_7	unknown_8*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????
*,
_read_only_resource_inputs

	
*-
config_proto

CPU

GPU 2J 8? *R
fMRK
I__inference_sequential_20_layer_call_and_return_conditional_losses_7579522
StatefulPartitionedCall?
IdentityIdentity StatefulPartitionedCall:output:0^StatefulPartitionedCall*
T0*'
_output_shapes
:?????????
2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*B
_input_shapes1
/:?????????: : : : : : : : : : 22
StatefulPartitionedCallStatefulPartitionedCall:W S
/
_output_shapes
:?????????
 
_user_specified_nameinputs
?
?
)__inference_dense_41_layer_call_fn_758641

inputs
unknown:d

	unknown_0:

identity??StatefulPartitionedCall?
StatefulPartitionedCallStatefulPartitionedCallinputsunknown	unknown_0*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????
*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *M
fHRF
D__inference_dense_41_layer_call_and_return_conditional_losses_7579452
StatefulPartitionedCall?
IdentityIdentity StatefulPartitionedCall:output:0^StatefulPartitionedCall*
T0*'
_output_shapes
:?????????
2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime**
_input_shapes
:?????????d: : 22
StatefulPartitionedCallStatefulPartitionedCall:O K
'
_output_shapes
:?????????d
 
_user_specified_nameinputs
?
?
R__inference_batch_normalization_14_layer_call_and_return_conditional_losses_758659

inputs%
readvariableop_resource: '
readvariableop_1_resource: 6
(fusedbatchnormv3_readvariableop_resource: 8
*fusedbatchnormv3_readvariableop_1_resource: 
identity??FusedBatchNormV3/ReadVariableOp?!FusedBatchNormV3/ReadVariableOp_1?ReadVariableOp?ReadVariableOp_1t
ReadVariableOpReadVariableOpreadvariableop_resource*
_output_shapes
: *
dtype02
ReadVariableOpz
ReadVariableOp_1ReadVariableOpreadvariableop_1_resource*
_output_shapes
: *
dtype02
ReadVariableOp_1?
FusedBatchNormV3/ReadVariableOpReadVariableOp(fusedbatchnormv3_readvariableop_resource*
_output_shapes
: *
dtype02!
FusedBatchNormV3/ReadVariableOp?
!FusedBatchNormV3/ReadVariableOp_1ReadVariableOp*fusedbatchnormv3_readvariableop_1_resource*
_output_shapes
: *
dtype02#
!FusedBatchNormV3/ReadVariableOp_1?
FusedBatchNormV3FusedBatchNormV3inputsReadVariableOp:value:0ReadVariableOp_1:value:0'FusedBatchNormV3/ReadVariableOp:value:0)FusedBatchNormV3/ReadVariableOp_1:value:0*
T0*
U0*]
_output_shapesK
I:+??????????????????????????? : : : : :*
epsilon%o?:*
is_training( 2
FusedBatchNormV3?
IdentityIdentityFusedBatchNormV3:y:0 ^FusedBatchNormV3/ReadVariableOp"^FusedBatchNormV3/ReadVariableOp_1^ReadVariableOp^ReadVariableOp_1*
T0*A
_output_shapes/
-:+??????????????????????????? 2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*H
_input_shapes7
5:+??????????????????????????? : : : : 2B
FusedBatchNormV3/ReadVariableOpFusedBatchNormV3/ReadVariableOp2F
!FusedBatchNormV3/ReadVariableOp_1!FusedBatchNormV3/ReadVariableOp_12 
ReadVariableOpReadVariableOp2$
ReadVariableOp_1ReadVariableOp_1:i e
A
_output_shapes/
-:+??????????????????????????? 
 
_user_specified_nameinputs
?<
?

I__inference_sequential_20_layer_call_and_return_conditional_losses_758416

inputsB
(conv2d_20_conv2d_readvariableop_resource: 7
)conv2d_20_biasadd_readvariableop_resource: N
@module_wrapper_14_batch_normalization_14_readvariableop_resource: P
Bmodule_wrapper_14_batch_normalization_14_readvariableop_1_resource: _
Qmodule_wrapper_14_batch_normalization_14_fusedbatchnormv3_readvariableop_resource: a
Smodule_wrapper_14_batch_normalization_14_fusedbatchnormv3_readvariableop_1_resource: :
'dense_40_matmul_readvariableop_resource:	?*d6
(dense_40_biasadd_readvariableop_resource:d9
'dense_41_matmul_readvariableop_resource:d
6
(dense_41_biasadd_readvariableop_resource:

identity?? conv2d_20/BiasAdd/ReadVariableOp?conv2d_20/Conv2D/ReadVariableOp?dense_40/BiasAdd/ReadVariableOp?dense_40/MatMul/ReadVariableOp?dense_41/BiasAdd/ReadVariableOp?dense_41/MatMul/ReadVariableOp?Hmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp?Jmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1?7module_wrapper_14/batch_normalization_14/ReadVariableOp?9module_wrapper_14/batch_normalization_14/ReadVariableOp_1?
conv2d_20/Conv2D/ReadVariableOpReadVariableOp(conv2d_20_conv2d_readvariableop_resource*&
_output_shapes
: *
dtype02!
conv2d_20/Conv2D/ReadVariableOp?
conv2d_20/Conv2DConv2Dinputs'conv2d_20/Conv2D/ReadVariableOp:value:0*
T0*/
_output_shapes
:????????? *
paddingVALID*
strides
2
conv2d_20/Conv2D?
 conv2d_20/BiasAdd/ReadVariableOpReadVariableOp)conv2d_20_biasadd_readvariableop_resource*
_output_shapes
: *
dtype02"
 conv2d_20/BiasAdd/ReadVariableOp?
conv2d_20/BiasAddBiasAddconv2d_20/Conv2D:output:0(conv2d_20/BiasAdd/ReadVariableOp:value:0*
T0*/
_output_shapes
:????????? 2
conv2d_20/BiasAdd~
conv2d_20/ReluReluconv2d_20/BiasAdd:output:0*
T0*/
_output_shapes
:????????? 2
conv2d_20/Relu?
7module_wrapper_14/batch_normalization_14/ReadVariableOpReadVariableOp@module_wrapper_14_batch_normalization_14_readvariableop_resource*
_output_shapes
: *
dtype029
7module_wrapper_14/batch_normalization_14/ReadVariableOp?
9module_wrapper_14/batch_normalization_14/ReadVariableOp_1ReadVariableOpBmodule_wrapper_14_batch_normalization_14_readvariableop_1_resource*
_output_shapes
: *
dtype02;
9module_wrapper_14/batch_normalization_14/ReadVariableOp_1?
Hmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOpReadVariableOpQmodule_wrapper_14_batch_normalization_14_fusedbatchnormv3_readvariableop_resource*
_output_shapes
: *
dtype02J
Hmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp?
Jmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1ReadVariableOpSmodule_wrapper_14_batch_normalization_14_fusedbatchnormv3_readvariableop_1_resource*
_output_shapes
: *
dtype02L
Jmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1?
9module_wrapper_14/batch_normalization_14/FusedBatchNormV3FusedBatchNormV3conv2d_20/Relu:activations:0?module_wrapper_14/batch_normalization_14/ReadVariableOp:value:0Amodule_wrapper_14/batch_normalization_14/ReadVariableOp_1:value:0Pmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp:value:0Rmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1:value:0*
T0*
U0*K
_output_shapes9
7:????????? : : : : :*
epsilon%o?:*
is_training( 2;
9module_wrapper_14/batch_normalization_14/FusedBatchNormV3?
max_pooling2d_20/MaxPoolMaxPool=module_wrapper_14/batch_normalization_14/FusedBatchNormV3:y:0*/
_output_shapes
:????????? *
ksize
*
paddingVALID*
strides
2
max_pooling2d_20/MaxPoolu
flatten_20/ConstConst*
_output_shapes
:*
dtype0*
valueB"????   2
flatten_20/Const?
flatten_20/ReshapeReshape!max_pooling2d_20/MaxPool:output:0flatten_20/Const:output:0*
T0*(
_output_shapes
:??????????*2
flatten_20/Reshape?
dense_40/MatMul/ReadVariableOpReadVariableOp'dense_40_matmul_readvariableop_resource*
_output_shapes
:	?*d*
dtype02 
dense_40/MatMul/ReadVariableOp?
dense_40/MatMulMatMulflatten_20/Reshape:output:0&dense_40/MatMul/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????d2
dense_40/MatMul?
dense_40/BiasAdd/ReadVariableOpReadVariableOp(dense_40_biasadd_readvariableop_resource*
_output_shapes
:d*
dtype02!
dense_40/BiasAdd/ReadVariableOp?
dense_40/BiasAddBiasAdddense_40/MatMul:product:0'dense_40/BiasAdd/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????d2
dense_40/BiasAdds
dense_40/ReluReludense_40/BiasAdd:output:0*
T0*'
_output_shapes
:?????????d2
dense_40/Relu?
dense_41/MatMul/ReadVariableOpReadVariableOp'dense_41_matmul_readvariableop_resource*
_output_shapes

:d
*
dtype02 
dense_41/MatMul/ReadVariableOp?
dense_41/MatMulMatMuldense_40/Relu:activations:0&dense_41/MatMul/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????
2
dense_41/MatMul?
dense_41/BiasAdd/ReadVariableOpReadVariableOp(dense_41_biasadd_readvariableop_resource*
_output_shapes
:
*
dtype02!
dense_41/BiasAdd/ReadVariableOp?
dense_41/BiasAddBiasAdddense_41/MatMul:product:0'dense_41/BiasAdd/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????
2
dense_41/BiasAdd|
dense_41/SoftmaxSoftmaxdense_41/BiasAdd:output:0*
T0*'
_output_shapes
:?????????
2
dense_41/Softmax?
IdentityIdentitydense_41/Softmax:softmax:0!^conv2d_20/BiasAdd/ReadVariableOp ^conv2d_20/Conv2D/ReadVariableOp ^dense_40/BiasAdd/ReadVariableOp^dense_40/MatMul/ReadVariableOp ^dense_41/BiasAdd/ReadVariableOp^dense_41/MatMul/ReadVariableOpI^module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOpK^module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_18^module_wrapper_14/batch_normalization_14/ReadVariableOp:^module_wrapper_14/batch_normalization_14/ReadVariableOp_1*
T0*'
_output_shapes
:?????????
2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*B
_input_shapes1
/:?????????: : : : : : : : : : 2D
 conv2d_20/BiasAdd/ReadVariableOp conv2d_20/BiasAdd/ReadVariableOp2B
conv2d_20/Conv2D/ReadVariableOpconv2d_20/Conv2D/ReadVariableOp2B
dense_40/BiasAdd/ReadVariableOpdense_40/BiasAdd/ReadVariableOp2@
dense_40/MatMul/ReadVariableOpdense_40/MatMul/ReadVariableOp2B
dense_41/BiasAdd/ReadVariableOpdense_41/BiasAdd/ReadVariableOp2@
dense_41/MatMul/ReadVariableOpdense_41/MatMul/ReadVariableOp2?
Hmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOpHmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp2?
Jmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1Jmodule_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_12r
7module_wrapper_14/batch_normalization_14/ReadVariableOp7module_wrapper_14/batch_normalization_14/ReadVariableOp2v
9module_wrapper_14/batch_normalization_14/ReadVariableOp_19module_wrapper_14/batch_normalization_14/ReadVariableOp_1:W S
/
_output_shapes
:?????????
 
_user_specified_nameinputs
?
?
M__inference_module_wrapper_14_layer_call_and_return_conditional_losses_757898

args_0<
.batch_normalization_14_readvariableop_resource: >
0batch_normalization_14_readvariableop_1_resource: M
?batch_normalization_14_fusedbatchnormv3_readvariableop_resource: O
Abatch_normalization_14_fusedbatchnormv3_readvariableop_1_resource: 
identity??6batch_normalization_14/FusedBatchNormV3/ReadVariableOp?8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1?%batch_normalization_14/ReadVariableOp?'batch_normalization_14/ReadVariableOp_1?
%batch_normalization_14/ReadVariableOpReadVariableOp.batch_normalization_14_readvariableop_resource*
_output_shapes
: *
dtype02'
%batch_normalization_14/ReadVariableOp?
'batch_normalization_14/ReadVariableOp_1ReadVariableOp0batch_normalization_14_readvariableop_1_resource*
_output_shapes
: *
dtype02)
'batch_normalization_14/ReadVariableOp_1?
6batch_normalization_14/FusedBatchNormV3/ReadVariableOpReadVariableOp?batch_normalization_14_fusedbatchnormv3_readvariableop_resource*
_output_shapes
: *
dtype028
6batch_normalization_14/FusedBatchNormV3/ReadVariableOp?
8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1ReadVariableOpAbatch_normalization_14_fusedbatchnormv3_readvariableop_1_resource*
_output_shapes
: *
dtype02:
8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1?
'batch_normalization_14/FusedBatchNormV3FusedBatchNormV3args_0-batch_normalization_14/ReadVariableOp:value:0/batch_normalization_14/ReadVariableOp_1:value:0>batch_normalization_14/FusedBatchNormV3/ReadVariableOp:value:0@batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1:value:0*
T0*
U0*K
_output_shapes9
7:????????? : : : : :*
epsilon%o?:*
is_training( 2)
'batch_normalization_14/FusedBatchNormV3?
IdentityIdentity+batch_normalization_14/FusedBatchNormV3:y:07^batch_normalization_14/FusedBatchNormV3/ReadVariableOp9^batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1&^batch_normalization_14/ReadVariableOp(^batch_normalization_14/ReadVariableOp_1*
T0*/
_output_shapes
:????????? 2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*6
_input_shapes%
#:????????? : : : : 2p
6batch_normalization_14/FusedBatchNormV3/ReadVariableOp6batch_normalization_14/FusedBatchNormV3/ReadVariableOp2t
8batch_normalization_14/FusedBatchNormV3/ReadVariableOp_18batch_normalization_14/FusedBatchNormV3/ReadVariableOp_12N
%batch_normalization_14/ReadVariableOp%batch_normalization_14/ReadVariableOp2R
'batch_normalization_14/ReadVariableOp_1'batch_normalization_14/ReadVariableOp_1:W S
/
_output_shapes
:????????? 
 
_user_specified_nameargs_0
?

?
D__inference_dense_41_layer_call_and_return_conditional_losses_757945

inputs0
matmul_readvariableop_resource:d
-
biasadd_readvariableop_resource:

identity??BiasAdd/ReadVariableOp?MatMul/ReadVariableOp?
MatMul/ReadVariableOpReadVariableOpmatmul_readvariableop_resource*
_output_shapes

:d
*
dtype02
MatMul/ReadVariableOps
MatMulMatMulinputsMatMul/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????
2
MatMul?
BiasAdd/ReadVariableOpReadVariableOpbiasadd_readvariableop_resource*
_output_shapes
:
*
dtype02
BiasAdd/ReadVariableOp?
BiasAddBiasAddMatMul:product:0BiasAdd/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????
2	
BiasAdda
SoftmaxSoftmaxBiasAdd:output:0*
T0*'
_output_shapes
:?????????
2	
Softmax?
IdentityIdentitySoftmax:softmax:0^BiasAdd/ReadVariableOp^MatMul/ReadVariableOp*
T0*'
_output_shapes
:?????????
2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime**
_input_shapes
:?????????d: : 20
BiasAdd/ReadVariableOpBiasAdd/ReadVariableOp2.
MatMul/ReadVariableOpMatMul/ReadVariableOp:O K
'
_output_shapes
:?????????d
 
_user_specified_nameinputs
?
b
F__inference_flatten_20_layer_call_and_return_conditional_losses_757915

inputs
identity_
ConstConst*
_output_shapes
:*
dtype0*
valueB"????   2
Consth
ReshapeReshapeinputsConst:output:0*
T0*(
_output_shapes
:??????????*2	
Reshapee
IdentityIdentityReshape:output:0*
T0*(
_output_shapes
:??????????*2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*.
_input_shapes
:????????? :W S
/
_output_shapes
:????????? 
 
_user_specified_nameinputs
?
G
+__inference_flatten_20_layer_call_fn_758601

inputs
identity?
PartitionedCallPartitionedCallinputs*
Tin
2*
Tout
2*
_collective_manager_ids
 *(
_output_shapes
:??????????** 
_read_only_resource_inputs
 *-
config_proto

CPU

GPU 2J 8? *O
fJRH
F__inference_flatten_20_layer_call_and_return_conditional_losses_7579152
PartitionedCallm
IdentityIdentityPartitionedCall:output:0*
T0*(
_output_shapes
:??????????*2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*.
_input_shapes
:????????? :W S
/
_output_shapes
:????????? 
 
_user_specified_nameinputs
?
?
)__inference_dense_40_layer_call_fn_758621

inputs
unknown:	?*d
	unknown_0:d
identity??StatefulPartitionedCall?
StatefulPartitionedCallStatefulPartitionedCallinputsunknown	unknown_0*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????d*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *M
fHRF
D__inference_dense_40_layer_call_and_return_conditional_losses_7579282
StatefulPartitionedCall?
IdentityIdentity StatefulPartitionedCall:output:0^StatefulPartitionedCall*
T0*'
_output_shapes
:?????????d2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*+
_input_shapes
:??????????*: : 22
StatefulPartitionedCallStatefulPartitionedCall:P L
(
_output_shapes
:??????????*
 
_user_specified_nameinputs
? 
?
I__inference_sequential_20_layer_call_and_return_conditional_losses_758191
conv2d_20_input*
conv2d_20_758164: 
conv2d_20_758166: &
module_wrapper_14_758169: &
module_wrapper_14_758171: &
module_wrapper_14_758173: &
module_wrapper_14_758175: "
dense_40_758180:	?*d
dense_40_758182:d!
dense_41_758185:d

dense_41_758187:

identity??!conv2d_20/StatefulPartitionedCall? dense_40/StatefulPartitionedCall? dense_41/StatefulPartitionedCall?)module_wrapper_14/StatefulPartitionedCall?
!conv2d_20/StatefulPartitionedCallStatefulPartitionedCallconv2d_20_inputconv2d_20_758164conv2d_20_758166*
Tin
2*
Tout
2*
_collective_manager_ids
 */
_output_shapes
:????????? *$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *N
fIRG
E__inference_conv2d_20_layer_call_and_return_conditional_losses_7578742#
!conv2d_20/StatefulPartitionedCall?
)module_wrapper_14/StatefulPartitionedCallStatefulPartitionedCall*conv2d_20/StatefulPartitionedCall:output:0module_wrapper_14_758169module_wrapper_14_758171module_wrapper_14_758173module_wrapper_14_758175*
Tin	
2*
Tout
2*
_collective_manager_ids
 */
_output_shapes
:????????? *&
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *V
fQRO
M__inference_module_wrapper_14_layer_call_and_return_conditional_losses_7578982+
)module_wrapper_14/StatefulPartitionedCall?
 max_pooling2d_20/PartitionedCallPartitionedCall2module_wrapper_14/StatefulPartitionedCall:output:0*
Tin
2*
Tout
2*
_collective_manager_ids
 */
_output_shapes
:????????? * 
_read_only_resource_inputs
 *-
config_proto

CPU

GPU 2J 8? *U
fPRN
L__inference_max_pooling2d_20_layer_call_and_return_conditional_losses_7578502"
 max_pooling2d_20/PartitionedCall?
flatten_20/PartitionedCallPartitionedCall)max_pooling2d_20/PartitionedCall:output:0*
Tin
2*
Tout
2*
_collective_manager_ids
 *(
_output_shapes
:??????????** 
_read_only_resource_inputs
 *-
config_proto

CPU

GPU 2J 8? *O
fJRH
F__inference_flatten_20_layer_call_and_return_conditional_losses_7579152
flatten_20/PartitionedCall?
 dense_40/StatefulPartitionedCallStatefulPartitionedCall#flatten_20/PartitionedCall:output:0dense_40_758180dense_40_758182*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????d*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *M
fHRF
D__inference_dense_40_layer_call_and_return_conditional_losses_7579282"
 dense_40/StatefulPartitionedCall?
 dense_41/StatefulPartitionedCallStatefulPartitionedCall)dense_40/StatefulPartitionedCall:output:0dense_41_758185dense_41_758187*
Tin
2*
Tout
2*
_collective_manager_ids
 *'
_output_shapes
:?????????
*$
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *M
fHRF
D__inference_dense_41_layer_call_and_return_conditional_losses_7579452"
 dense_41/StatefulPartitionedCall?
IdentityIdentity)dense_41/StatefulPartitionedCall:output:0"^conv2d_20/StatefulPartitionedCall!^dense_40/StatefulPartitionedCall!^dense_41/StatefulPartitionedCall*^module_wrapper_14/StatefulPartitionedCall*
T0*'
_output_shapes
:?????????
2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*B
_input_shapes1
/:?????????: : : : : : : : : : 2F
!conv2d_20/StatefulPartitionedCall!conv2d_20/StatefulPartitionedCall2D
 dense_40/StatefulPartitionedCall dense_40/StatefulPartitionedCall2D
 dense_41/StatefulPartitionedCall dense_41/StatefulPartitionedCall2V
)module_wrapper_14/StatefulPartitionedCall)module_wrapper_14/StatefulPartitionedCall:` \
/
_output_shapes
:?????????
)
_user_specified_nameconv2d_20_input
?(
?
__inference__traced_save_758768
file_prefix/
+savev2_conv2d_20_kernel_read_readvariableop-
)savev2_conv2d_20_bias_read_readvariableop.
*savev2_dense_40_kernel_read_readvariableop,
(savev2_dense_40_bias_read_readvariableop.
*savev2_dense_41_kernel_read_readvariableop,
(savev2_dense_41_bias_read_readvariableopM
Isavev2_module_wrapper_14_batch_normalization_14_gamma_read_readvariableopL
Hsavev2_module_wrapper_14_batch_normalization_14_beta_read_readvariableopS
Osavev2_module_wrapper_14_batch_normalization_14_moving_mean_read_readvariableopW
Ssavev2_module_wrapper_14_batch_normalization_14_moving_variance_read_readvariableop$
 savev2_total_read_readvariableop$
 savev2_count_read_readvariableop&
"savev2_total_1_read_readvariableop&
"savev2_count_1_read_readvariableop
savev2_const

identity_1??MergeV2Checkpoints?
StaticRegexFullMatchStaticRegexFullMatchfile_prefix"/device:CPU:**
_output_shapes
: *
pattern
^s3://.*2
StaticRegexFullMatchc
ConstConst"/device:CPU:**
_output_shapes
: *
dtype0*
valueB B.part2
Constl
Const_1Const"/device:CPU:**
_output_shapes
: *
dtype0*
valueB B
_temp/part2	
Const_1?
SelectSelectStaticRegexFullMatch:output:0Const:output:0Const_1:output:0"/device:CPU:**
T0*
_output_shapes
: 2
Selectt

StringJoin
StringJoinfile_prefixSelect:output:0"/device:CPU:**
N*
_output_shapes
: 2

StringJoinZ

num_shardsConst*
_output_shapes
: *
dtype0*
value	B :2

num_shards
ShardedFilename/shardConst"/device:CPU:0*
_output_shapes
: *
dtype0*
value	B : 2
ShardedFilename/shard?
ShardedFilenameShardedFilenameStringJoin:output:0ShardedFilename/shard:output:0num_shards:output:0"/device:CPU:0*
_output_shapes
: 2
ShardedFilename?
SaveV2/tensor_namesConst"/device:CPU:0*
_output_shapes
:*
dtype0*?
value?B?B6layer_with_weights-0/kernel/.ATTRIBUTES/VARIABLE_VALUEB4layer_with_weights-0/bias/.ATTRIBUTES/VARIABLE_VALUEB6layer_with_weights-2/kernel/.ATTRIBUTES/VARIABLE_VALUEB4layer_with_weights-2/bias/.ATTRIBUTES/VARIABLE_VALUEB6layer_with_weights-3/kernel/.ATTRIBUTES/VARIABLE_VALUEB4layer_with_weights-3/bias/.ATTRIBUTES/VARIABLE_VALUEB&variables/2/.ATTRIBUTES/VARIABLE_VALUEB&variables/3/.ATTRIBUTES/VARIABLE_VALUEB&variables/4/.ATTRIBUTES/VARIABLE_VALUEB&variables/5/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/0/total/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/0/count/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/1/total/.ATTRIBUTES/VARIABLE_VALUEB4keras_api/metrics/1/count/.ATTRIBUTES/VARIABLE_VALUEB_CHECKPOINTABLE_OBJECT_GRAPH2
SaveV2/tensor_names?
SaveV2/shape_and_slicesConst"/device:CPU:0*
_output_shapes
:*
dtype0*1
value(B&B B B B B B B B B B B B B B B 2
SaveV2/shape_and_slices?
SaveV2SaveV2ShardedFilename:filename:0SaveV2/tensor_names:output:0 SaveV2/shape_and_slices:output:0+savev2_conv2d_20_kernel_read_readvariableop)savev2_conv2d_20_bias_read_readvariableop*savev2_dense_40_kernel_read_readvariableop(savev2_dense_40_bias_read_readvariableop*savev2_dense_41_kernel_read_readvariableop(savev2_dense_41_bias_read_readvariableopIsavev2_module_wrapper_14_batch_normalization_14_gamma_read_readvariableopHsavev2_module_wrapper_14_batch_normalization_14_beta_read_readvariableopOsavev2_module_wrapper_14_batch_normalization_14_moving_mean_read_readvariableopSsavev2_module_wrapper_14_batch_normalization_14_moving_variance_read_readvariableop savev2_total_read_readvariableop savev2_count_read_readvariableop"savev2_total_1_read_readvariableop"savev2_count_1_read_readvariableopsavev2_const"/device:CPU:0*
_output_shapes
 *
dtypes
22
SaveV2?
&MergeV2Checkpoints/checkpoint_prefixesPackShardedFilename:filename:0^SaveV2"/device:CPU:0*
N*
T0*
_output_shapes
:2(
&MergeV2Checkpoints/checkpoint_prefixes?
MergeV2CheckpointsMergeV2Checkpoints/MergeV2Checkpoints/checkpoint_prefixes:output:0file_prefix"/device:CPU:0*
_output_shapes
 2
MergeV2Checkpointsr
IdentityIdentityfile_prefix^MergeV2Checkpoints"/device:CPU:0*
T0*
_output_shapes
: 2

Identitym

Identity_1IdentityIdentity:output:0^MergeV2Checkpoints*
T0*
_output_shapes
: 2

Identity_1"!

identity_1Identity_1:output:0*p
_input_shapes_
]: : : :	?*d:d:d
:
: : : : : : : : : 2(
MergeV2CheckpointsMergeV2Checkpoints:C ?

_output_shapes
: 
%
_user_specified_namefile_prefix:,(
&
_output_shapes
: : 

_output_shapes
: :%!

_output_shapes
:	?*d: 

_output_shapes
:d:$ 

_output_shapes

:d
: 

_output_shapes
:
: 

_output_shapes
: : 

_output_shapes
: : 	

_output_shapes
: : 


_output_shapes
: :

_output_shapes
: :

_output_shapes
: :

_output_shapes
: :

_output_shapes
: :

_output_shapes
: 
?J
?
!__inference__wrapped_model_757844
conv2d_20_inputP
6sequential_20_conv2d_20_conv2d_readvariableop_resource: E
7sequential_20_conv2d_20_biasadd_readvariableop_resource: \
Nsequential_20_module_wrapper_14_batch_normalization_14_readvariableop_resource: ^
Psequential_20_module_wrapper_14_batch_normalization_14_readvariableop_1_resource: m
_sequential_20_module_wrapper_14_batch_normalization_14_fusedbatchnormv3_readvariableop_resource: o
asequential_20_module_wrapper_14_batch_normalization_14_fusedbatchnormv3_readvariableop_1_resource: H
5sequential_20_dense_40_matmul_readvariableop_resource:	?*dD
6sequential_20_dense_40_biasadd_readvariableop_resource:dG
5sequential_20_dense_41_matmul_readvariableop_resource:d
D
6sequential_20_dense_41_biasadd_readvariableop_resource:

identity??.sequential_20/conv2d_20/BiasAdd/ReadVariableOp?-sequential_20/conv2d_20/Conv2D/ReadVariableOp?-sequential_20/dense_40/BiasAdd/ReadVariableOp?,sequential_20/dense_40/MatMul/ReadVariableOp?-sequential_20/dense_41/BiasAdd/ReadVariableOp?,sequential_20/dense_41/MatMul/ReadVariableOp?Vsequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp?Xsequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1?Esequential_20/module_wrapper_14/batch_normalization_14/ReadVariableOp?Gsequential_20/module_wrapper_14/batch_normalization_14/ReadVariableOp_1?
-sequential_20/conv2d_20/Conv2D/ReadVariableOpReadVariableOp6sequential_20_conv2d_20_conv2d_readvariableop_resource*&
_output_shapes
: *
dtype02/
-sequential_20/conv2d_20/Conv2D/ReadVariableOp?
sequential_20/conv2d_20/Conv2DConv2Dconv2d_20_input5sequential_20/conv2d_20/Conv2D/ReadVariableOp:value:0*
T0*/
_output_shapes
:????????? *
paddingVALID*
strides
2 
sequential_20/conv2d_20/Conv2D?
.sequential_20/conv2d_20/BiasAdd/ReadVariableOpReadVariableOp7sequential_20_conv2d_20_biasadd_readvariableop_resource*
_output_shapes
: *
dtype020
.sequential_20/conv2d_20/BiasAdd/ReadVariableOp?
sequential_20/conv2d_20/BiasAddBiasAdd'sequential_20/conv2d_20/Conv2D:output:06sequential_20/conv2d_20/BiasAdd/ReadVariableOp:value:0*
T0*/
_output_shapes
:????????? 2!
sequential_20/conv2d_20/BiasAdd?
sequential_20/conv2d_20/ReluRelu(sequential_20/conv2d_20/BiasAdd:output:0*
T0*/
_output_shapes
:????????? 2
sequential_20/conv2d_20/Relu?
Esequential_20/module_wrapper_14/batch_normalization_14/ReadVariableOpReadVariableOpNsequential_20_module_wrapper_14_batch_normalization_14_readvariableop_resource*
_output_shapes
: *
dtype02G
Esequential_20/module_wrapper_14/batch_normalization_14/ReadVariableOp?
Gsequential_20/module_wrapper_14/batch_normalization_14/ReadVariableOp_1ReadVariableOpPsequential_20_module_wrapper_14_batch_normalization_14_readvariableop_1_resource*
_output_shapes
: *
dtype02I
Gsequential_20/module_wrapper_14/batch_normalization_14/ReadVariableOp_1?
Vsequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOpReadVariableOp_sequential_20_module_wrapper_14_batch_normalization_14_fusedbatchnormv3_readvariableop_resource*
_output_shapes
: *
dtype02X
Vsequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp?
Xsequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1ReadVariableOpasequential_20_module_wrapper_14_batch_normalization_14_fusedbatchnormv3_readvariableop_1_resource*
_output_shapes
: *
dtype02Z
Xsequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1?
Gsequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3FusedBatchNormV3*sequential_20/conv2d_20/Relu:activations:0Msequential_20/module_wrapper_14/batch_normalization_14/ReadVariableOp:value:0Osequential_20/module_wrapper_14/batch_normalization_14/ReadVariableOp_1:value:0^sequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp:value:0`sequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1:value:0*
T0*
U0*K
_output_shapes9
7:????????? : : : : :*
epsilon%o?:*
is_training( 2I
Gsequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3?
&sequential_20/max_pooling2d_20/MaxPoolMaxPoolKsequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3:y:0*/
_output_shapes
:????????? *
ksize
*
paddingVALID*
strides
2(
&sequential_20/max_pooling2d_20/MaxPool?
sequential_20/flatten_20/ConstConst*
_output_shapes
:*
dtype0*
valueB"????   2 
sequential_20/flatten_20/Const?
 sequential_20/flatten_20/ReshapeReshape/sequential_20/max_pooling2d_20/MaxPool:output:0'sequential_20/flatten_20/Const:output:0*
T0*(
_output_shapes
:??????????*2"
 sequential_20/flatten_20/Reshape?
,sequential_20/dense_40/MatMul/ReadVariableOpReadVariableOp5sequential_20_dense_40_matmul_readvariableop_resource*
_output_shapes
:	?*d*
dtype02.
,sequential_20/dense_40/MatMul/ReadVariableOp?
sequential_20/dense_40/MatMulMatMul)sequential_20/flatten_20/Reshape:output:04sequential_20/dense_40/MatMul/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????d2
sequential_20/dense_40/MatMul?
-sequential_20/dense_40/BiasAdd/ReadVariableOpReadVariableOp6sequential_20_dense_40_biasadd_readvariableop_resource*
_output_shapes
:d*
dtype02/
-sequential_20/dense_40/BiasAdd/ReadVariableOp?
sequential_20/dense_40/BiasAddBiasAdd'sequential_20/dense_40/MatMul:product:05sequential_20/dense_40/BiasAdd/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????d2 
sequential_20/dense_40/BiasAdd?
sequential_20/dense_40/ReluRelu'sequential_20/dense_40/BiasAdd:output:0*
T0*'
_output_shapes
:?????????d2
sequential_20/dense_40/Relu?
,sequential_20/dense_41/MatMul/ReadVariableOpReadVariableOp5sequential_20_dense_41_matmul_readvariableop_resource*
_output_shapes

:d
*
dtype02.
,sequential_20/dense_41/MatMul/ReadVariableOp?
sequential_20/dense_41/MatMulMatMul)sequential_20/dense_40/Relu:activations:04sequential_20/dense_41/MatMul/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????
2
sequential_20/dense_41/MatMul?
-sequential_20/dense_41/BiasAdd/ReadVariableOpReadVariableOp6sequential_20_dense_41_biasadd_readvariableop_resource*
_output_shapes
:
*
dtype02/
-sequential_20/dense_41/BiasAdd/ReadVariableOp?
sequential_20/dense_41/BiasAddBiasAdd'sequential_20/dense_41/MatMul:product:05sequential_20/dense_41/BiasAdd/ReadVariableOp:value:0*
T0*'
_output_shapes
:?????????
2 
sequential_20/dense_41/BiasAdd?
sequential_20/dense_41/SoftmaxSoftmax'sequential_20/dense_41/BiasAdd:output:0*
T0*'
_output_shapes
:?????????
2 
sequential_20/dense_41/Softmax?
IdentityIdentity(sequential_20/dense_41/Softmax:softmax:0/^sequential_20/conv2d_20/BiasAdd/ReadVariableOp.^sequential_20/conv2d_20/Conv2D/ReadVariableOp.^sequential_20/dense_40/BiasAdd/ReadVariableOp-^sequential_20/dense_40/MatMul/ReadVariableOp.^sequential_20/dense_41/BiasAdd/ReadVariableOp-^sequential_20/dense_41/MatMul/ReadVariableOpW^sequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOpY^sequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1F^sequential_20/module_wrapper_14/batch_normalization_14/ReadVariableOpH^sequential_20/module_wrapper_14/batch_normalization_14/ReadVariableOp_1*
T0*'
_output_shapes
:?????????
2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*B
_input_shapes1
/:?????????: : : : : : : : : : 2`
.sequential_20/conv2d_20/BiasAdd/ReadVariableOp.sequential_20/conv2d_20/BiasAdd/ReadVariableOp2^
-sequential_20/conv2d_20/Conv2D/ReadVariableOp-sequential_20/conv2d_20/Conv2D/ReadVariableOp2^
-sequential_20/dense_40/BiasAdd/ReadVariableOp-sequential_20/dense_40/BiasAdd/ReadVariableOp2\
,sequential_20/dense_40/MatMul/ReadVariableOp,sequential_20/dense_40/MatMul/ReadVariableOp2^
-sequential_20/dense_41/BiasAdd/ReadVariableOp-sequential_20/dense_41/BiasAdd/ReadVariableOp2\
,sequential_20/dense_41/MatMul/ReadVariableOp,sequential_20/dense_41/MatMul/ReadVariableOp2?
Vsequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOpVsequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp2?
Xsequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_1Xsequential_20/module_wrapper_14/batch_normalization_14/FusedBatchNormV3/ReadVariableOp_12?
Esequential_20/module_wrapper_14/batch_normalization_14/ReadVariableOpEsequential_20/module_wrapper_14/batch_normalization_14/ReadVariableOp2?
Gsequential_20/module_wrapper_14/batch_normalization_14/ReadVariableOp_1Gsequential_20/module_wrapper_14/batch_normalization_14/ReadVariableOp_1:` \
/
_output_shapes
:?????????
)
_user_specified_nameconv2d_20_input
?
?
2__inference_module_wrapper_14_layer_call_fn_758577

args_0
unknown: 
	unknown_0: 
	unknown_1: 
	unknown_2: 
identity??StatefulPartitionedCall?
StatefulPartitionedCallStatefulPartitionedCallargs_0unknown	unknown_0	unknown_1	unknown_2*
Tin	
2*
Tout
2*
_collective_manager_ids
 */
_output_shapes
:????????? *&
_read_only_resource_inputs
*-
config_proto

CPU

GPU 2J 8? *V
fQRO
M__inference_module_wrapper_14_layer_call_and_return_conditional_losses_7578982
StatefulPartitionedCall?
IdentityIdentity StatefulPartitionedCall:output:0^StatefulPartitionedCall*
T0*/
_output_shapes
:????????? 2

Identity"
identityIdentity:output:0*(
_construction_contextkEagerRuntime*6
_input_shapes%
#:????????? : : : : 22
StatefulPartitionedCallStatefulPartitionedCall:W S
/
_output_shapes
:????????? 
 
_user_specified_nameargs_0"?L
saver_filename:0StatefulPartitionedCall_1:0StatefulPartitionedCall_28"
saved_model_main_op

NoOp*>
__saved_model_init_op%#
__saved_model_init_op

NoOp*?
serving_default?
S
conv2d_20_input@
!serving_default_conv2d_20_input:0?????????<
dense_410
StatefulPartitionedCall:0?????????
tensorflow/serving/predict:??
?
layer_with_weights-0
layer-0
layer_with_weights-1
layer-1
layer-2
layer-3
layer_with_weights-2
layer-4
layer_with_weights-3
layer-5
	optimizer
regularization_losses
		variables

trainable_variables
	keras_api

signatures
*h&call_and_return_all_conditional_losses
i_default_save_signature
j__call__"?
_tf_keras_sequential?{"name": "sequential_20", "trainable": true, "expects_training_arg": true, "dtype": "float32", "batch_input_shape": null, "must_restore_from_config": false, "class_name": "Sequential", "config": {"name": "sequential_20", "layers": [{"class_name": "InputLayer", "config": {"batch_input_shape": {"class_name": "__tuple__", "items": [null, 28, 28, 1]}, "dtype": "float32", "sparse": false, "ragged": false, "name": "conv2d_20_input"}}, {"class_name": "Conv2D", "config": {"name": "conv2d_20", "trainable": true, "batch_input_shape": {"class_name": "__tuple__", "items": [null, 28, 28, 1]}, "dtype": "float32", "filters": 32, "kernel_size": {"class_name": "__tuple__", "items": [3, 3]}, "strides": {"class_name": "__tuple__", "items": [1, 1]}, "padding": "valid", "data_format": "channels_last", "dilation_rate": {"class_name": "__tuple__", "items": [1, 1]}, "groups": 1, "activation": "relu", "use_bias": true, "kernel_initializer": {"class_name": "HeUniform", "config": {"seed": null}}, "bias_initializer": {"class_name": "Zeros", "config": {}}, "kernel_regularizer": null, "bias_regularizer": null, "activity_regularizer": null, "kernel_constraint": null, "bias_constraint": null}}, {"class_name": "ModuleWrapper", "config": {"layer was saved without config": true}}, {"class_name": "MaxPooling2D", "config": {"name": "max_pooling2d_20", "trainable": true, "dtype": "float32", "pool_size": {"class_name": "__tuple__", "items": [2, 2]}, "padding": "valid", "strides": {"class_name": "__tuple__", "items": [2, 2]}, "data_format": "channels_last"}}, {"class_name": "Flatten", "config": {"name": "flatten_20", "trainable": true, "dtype": "float32", "data_format": "channels_last"}}, {"class_name": "Dense", "config": {"name": "dense_40", "trainable": true, "dtype": "float32", "units": 100, "activation": "relu", "use_bias": true, "kernel_initializer": {"class_name": "HeUniform", "config": {"seed": null}}, "bias_initializer": {"class_name": "Zeros", "config": {}}, "kernel_regularizer": null, "bias_regularizer": null, "activity_regularizer": null, "kernel_constraint": null, "bias_constraint": null}}, {"class_name": "Dense", "config": {"name": "dense_41", "trainable": true, "dtype": "float32", "units": 10, "activation": "softmax", "use_bias": true, "kernel_initializer": {"class_name": "GlorotUniform", "config": {"seed": null}}, "bias_initializer": {"class_name": "Zeros", "config": {}}, "kernel_regularizer": null, "bias_regularizer": null, "activity_regularizer": null, "kernel_constraint": null, "bias_constraint": null}}]}, "shared_object_id": 12, "input_spec": {"class_name": "InputSpec", "config": {"dtype": null, "shape": null, "ndim": null, "max_ndim": null, "min_ndim": 4, "axes": {"-1": 1}}, "shared_object_id": 13}, "build_input_shape": {"class_name": "TensorShape", "items": [null, 28, 28, 1]}, "is_graph_network": true, "save_spec": {"class_name": "TypeSpec", "type_spec": "tf.TensorSpec", "serialized": [{"class_name": "TensorShape", "items": [null, 28, 28, 1]}, "float32", "conv2d_20_input"]}, "keras_version": "2.5.0", "backend": "tensorflow", "model_config": {"class_name": "Sequential"}, "training_config": {"loss": "categorical_crossentropy", "metrics": [[{"class_name": "MeanMetricWrapper", "config": {"name": "accuracy", "dtype": "float32", "fn": "categorical_accuracy"}, "shared_object_id": 14}]], "weighted_metrics": null, "loss_weights": null, "optimizer_config": {"class_name": "SGD", "config": {"name": "SGD", "learning_rate": 0.01, "decay": 0.0, "momentum": 0.9, "nesterov": false}}}}
?

kernel
bias
regularization_losses
	variables
trainable_variables
	keras_api
*k&call_and_return_all_conditional_losses
l__call__"?

_tf_keras_layer?
{"name": "conv2d_20", "trainable": true, "expects_training_arg": false, "dtype": "float32", "batch_input_shape": {"class_name": "__tuple__", "items": [null, 28, 28, 1]}, "stateful": false, "must_restore_from_config": false, "class_name": "Conv2D", "config": {"name": "conv2d_20", "trainable": true, "batch_input_shape": {"class_name": "__tuple__", "items": [null, 28, 28, 1]}, "dtype": "float32", "filters": 32, "kernel_size": {"class_name": "__tuple__", "items": [3, 3]}, "strides": {"class_name": "__tuple__", "items": [1, 1]}, "padding": "valid", "data_format": "channels_last", "dilation_rate": {"class_name": "__tuple__", "items": [1, 1]}, "groups": 1, "activation": "relu", "use_bias": true, "kernel_initializer": {"class_name": "HeUniform", "config": {"seed": null}, "shared_object_id": 1}, "bias_initializer": {"class_name": "Zeros", "config": {}, "shared_object_id": 2}, "kernel_regularizer": null, "bias_regularizer": null, "activity_regularizer": null, "kernel_constraint": null, "bias_constraint": null}, "shared_object_id": 3, "input_spec": {"class_name": "InputSpec", "config": {"dtype": null, "shape": null, "ndim": null, "max_ndim": null, "min_ndim": 4, "axes": {"-1": 1}}, "shared_object_id": 13}, "build_input_shape": {"class_name": "TensorShape", "items": [null, 28, 28, 1]}}
?
_module
regularization_losses
	variables
trainable_variables
	keras_api
*m&call_and_return_all_conditional_losses
n__call__"?
_tf_keras_layer?{"name": "module_wrapper_14", "trainable": true, "expects_training_arg": true, "dtype": "float32", "batch_input_shape": null, "stateful": false, "must_restore_from_config": false, "class_name": "ModuleWrapper", "config": {"layer was saved without config": true}}
?
regularization_losses
	variables
trainable_variables
	keras_api
*o&call_and_return_all_conditional_losses
p__call__"?
_tf_keras_layer?{"name": "max_pooling2d_20", "trainable": true, "expects_training_arg": false, "dtype": "float32", "batch_input_shape": null, "stateful": false, "must_restore_from_config": false, "class_name": "MaxPooling2D", "config": {"name": "max_pooling2d_20", "trainable": true, "dtype": "float32", "pool_size": {"class_name": "__tuple__", "items": [2, 2]}, "padding": "valid", "strides": {"class_name": "__tuple__", "items": [2, 2]}, "data_format": "channels_last"}, "shared_object_id": 4, "input_spec": {"class_name": "InputSpec", "config": {"dtype": null, "shape": null, "ndim": 4, "max_ndim": null, "min_ndim": null, "axes": {}}, "shared_object_id": 15}}
?
regularization_losses
	variables
trainable_variables
	keras_api
*q&call_and_return_all_conditional_losses
r__call__"?
_tf_keras_layer?{"name": "flatten_20", "trainable": true, "expects_training_arg": false, "dtype": "float32", "batch_input_shape": null, "stateful": false, "must_restore_from_config": false, "class_name": "Flatten", "config": {"name": "flatten_20", "trainable": true, "dtype": "float32", "data_format": "channels_last"}, "shared_object_id": 5, "input_spec": {"class_name": "InputSpec", "config": {"dtype": null, "shape": null, "ndim": null, "max_ndim": null, "min_ndim": 1, "axes": {}}, "shared_object_id": 16}}
?

 kernel
!bias
"regularization_losses
#	variables
$trainable_variables
%	keras_api
*s&call_and_return_all_conditional_losses
t__call__"?
_tf_keras_layer?{"name": "dense_40", "trainable": true, "expects_training_arg": false, "dtype": "float32", "batch_input_shape": null, "stateful": false, "must_restore_from_config": false, "class_name": "Dense", "config": {"name": "dense_40", "trainable": true, "dtype": "float32", "units": 100, "activation": "relu", "use_bias": true, "kernel_initializer": {"class_name": "HeUniform", "config": {"seed": null}, "shared_object_id": 6}, "bias_initializer": {"class_name": "Zeros", "config": {}, "shared_object_id": 7}, "kernel_regularizer": null, "bias_regularizer": null, "activity_regularizer": null, "kernel_constraint": null, "bias_constraint": null}, "shared_object_id": 8, "input_spec": {"class_name": "InputSpec", "config": {"dtype": null, "shape": null, "ndim": null, "max_ndim": null, "min_ndim": 2, "axes": {"-1": 5408}}, "shared_object_id": 17}, "build_input_shape": {"class_name": "TensorShape", "items": [null, 5408]}}
?

&kernel
'bias
(regularization_losses
)	variables
*trainable_variables
+	keras_api
*u&call_and_return_all_conditional_losses
v__call__"?
_tf_keras_layer?{"name": "dense_41", "trainable": true, "expects_training_arg": false, "dtype": "float32", "batch_input_shape": null, "stateful": false, "must_restore_from_config": false, "class_name": "Dense", "config": {"name": "dense_41", "trainable": true, "dtype": "float32", "units": 10, "activation": "softmax", "use_bias": true, "kernel_initializer": {"class_name": "GlorotUniform", "config": {"seed": null}, "shared_object_id": 9}, "bias_initializer": {"class_name": "Zeros", "config": {}, "shared_object_id": 10}, "kernel_regularizer": null, "bias_regularizer": null, "activity_regularizer": null, "kernel_constraint": null, "bias_constraint": null}, "shared_object_id": 11, "input_spec": {"class_name": "InputSpec", "config": {"dtype": null, "shape": null, "ndim": null, "max_ndim": null, "min_ndim": 2, "axes": {"-1": 100}}, "shared_object_id": 18}, "build_input_shape": {"class_name": "TensorShape", "items": [null, 100]}}
"
	optimizer
 "
trackable_list_wrapper
f
0
1
,2
-3
.4
/5
 6
!7
&8
'9"
trackable_list_wrapper
X
0
1
,2
-3
 4
!5
&6
'7"
trackable_list_wrapper
?
0metrics
1layer_regularization_losses
2layer_metrics
regularization_losses

3layers
		variables

trainable_variables
4non_trainable_variables
j__call__
i_default_save_signature
*h&call_and_return_all_conditional_losses
&h"call_and_return_conditional_losses"
_generic_user_object
,
wserving_default"
signature_map
*:( 2conv2d_20/kernel
: 2conv2d_20/bias
 "
trackable_list_wrapper
.
0
1"
trackable_list_wrapper
.
0
1"
trackable_list_wrapper
?
5layer_regularization_losses
6non_trainable_variables
7layer_metrics
regularization_losses

8layers
	variables
trainable_variables
9metrics
l__call__
*k&call_and_return_all_conditional_losses
&k"call_and_return_conditional_losses"
_generic_user_object
?	
:axis
	,gamma
-beta
.moving_mean
/moving_variance
;regularization_losses
<	variables
=trainable_variables
>	keras_api
*x&call_and_return_all_conditional_losses
y__call__"?
_tf_keras_layer?{"name": "batch_normalization_14", "trainable": true, "expects_training_arg": true, "dtype": "float32", "batch_input_shape": null, "stateful": false, "must_restore_from_config": false, "class_name": "BatchNormalization", "config": {"name": "batch_normalization_14", "trainable": true, "dtype": "float32", "axis": [3], "momentum": 0.99, "epsilon": 0.001, "center": true, "scale": true, "beta_initializer": {"class_name": "Zeros", "config": {}}, "gamma_initializer": {"class_name": "Ones", "config": {}}, "moving_mean_initializer": {"class_name": "Zeros", "config": {}}, "moving_variance_initializer": {"class_name": "Ones", "config": {}}, "beta_regularizer": null, "gamma_regularizer": null, "beta_constraint": null, "gamma_constraint": null}, "input_spec": {"class_name": "InputSpec", "config": {"dtype": null, "shape": null, "ndim": 4, "max_ndim": null, "min_ndim": null, "axes": {"3": 32}}}, "build_input_shape": {"class_name": "TensorShape", "items": [null, 26, 26, 32]}}
 "
trackable_list_wrapper
<
,0
-1
.2
/3"
trackable_list_wrapper
.
,0
-1"
trackable_list_wrapper
?
?layer_regularization_losses
@non_trainable_variables
Alayer_metrics
regularization_losses

Blayers
	variables
trainable_variables
Cmetrics
n__call__
*m&call_and_return_all_conditional_losses
&m"call_and_return_conditional_losses"
_generic_user_object
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
?
Dlayer_regularization_losses
Enon_trainable_variables
Flayer_metrics
regularization_losses

Glayers
	variables
trainable_variables
Hmetrics
p__call__
*o&call_and_return_all_conditional_losses
&o"call_and_return_conditional_losses"
_generic_user_object
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
?
Ilayer_regularization_losses
Jnon_trainable_variables
Klayer_metrics
regularization_losses

Llayers
	variables
trainable_variables
Mmetrics
r__call__
*q&call_and_return_all_conditional_losses
&q"call_and_return_conditional_losses"
_generic_user_object
": 	?*d2dense_40/kernel
:d2dense_40/bias
 "
trackable_list_wrapper
.
 0
!1"
trackable_list_wrapper
.
 0
!1"
trackable_list_wrapper
?
Nlayer_regularization_losses
Onon_trainable_variables
Player_metrics
"regularization_losses

Qlayers
#	variables
$trainable_variables
Rmetrics
t__call__
*s&call_and_return_all_conditional_losses
&s"call_and_return_conditional_losses"
_generic_user_object
!:d
2dense_41/kernel
:
2dense_41/bias
 "
trackable_list_wrapper
.
&0
'1"
trackable_list_wrapper
.
&0
'1"
trackable_list_wrapper
?
Slayer_regularization_losses
Tnon_trainable_variables
Ulayer_metrics
(regularization_losses

Vlayers
)	variables
*trainable_variables
Wmetrics
v__call__
*u&call_and_return_all_conditional_losses
&u"call_and_return_conditional_losses"
_generic_user_object
<:: 2.module_wrapper_14/batch_normalization_14/gamma
;:9 2-module_wrapper_14/batch_normalization_14/beta
D:B  (24module_wrapper_14/batch_normalization_14/moving_mean
H:F  (28module_wrapper_14/batch_normalization_14/moving_variance
.
X0
Y1"
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_dict_wrapper
J
0
1
2
3
4
5"
trackable_list_wrapper
.
.0
/1"
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_dict_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
<
,0
-1
.2
/3"
trackable_list_wrapper
.
,0
-1"
trackable_list_wrapper
?
Zlayer_regularization_losses
[non_trainable_variables
\layer_metrics
;regularization_losses

]layers
<	variables
=trainable_variables
^metrics
y__call__
*x&call_and_return_all_conditional_losses
&x"call_and_return_conditional_losses"
_generic_user_object
 "
trackable_list_wrapper
.
.0
/1"
trackable_list_wrapper
 "
trackable_dict_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_dict_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_dict_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_dict_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
 "
trackable_dict_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
?
	_total
	`count
a	variables
b	keras_api"?
_tf_keras_metric?{"class_name": "Mean", "name": "loss", "dtype": "float32", "config": {"name": "loss", "dtype": "float32"}, "shared_object_id": 19}
?
	ctotal
	dcount
e
_fn_kwargs
f	variables
g	keras_api"?
_tf_keras_metric?{"class_name": "MeanMetricWrapper", "name": "accuracy", "dtype": "float32", "config": {"name": "accuracy", "dtype": "float32", "fn": "categorical_accuracy"}, "shared_object_id": 14}
 "
trackable_list_wrapper
.
.0
/1"
trackable_list_wrapper
 "
trackable_dict_wrapper
 "
trackable_list_wrapper
 "
trackable_list_wrapper
:  (2total
:  (2count
.
_0
`1"
trackable_list_wrapper
-
a	variables"
_generic_user_object
:  (2total
:  (2count
 "
trackable_dict_wrapper
.
c0
d1"
trackable_list_wrapper
-
f	variables"
_generic_user_object
?2?
I__inference_sequential_20_layer_call_and_return_conditional_losses_758416
I__inference_sequential_20_layer_call_and_return_conditional_losses_758458
I__inference_sequential_20_layer_call_and_return_conditional_losses_758191
I__inference_sequential_20_layer_call_and_return_conditional_losses_758221?
???
FullArgSpec1
args)?&
jself
jinputs

jtraining
jmask
varargs
 
varkw
 
defaults?
p 

 

kwonlyargs? 
kwonlydefaults? 
annotations? *
 
?2?
!__inference__wrapped_model_757844?
???
FullArgSpec
args? 
varargsjargs
varkw
 
defaults
 

kwonlyargs? 
kwonlydefaults
 
annotations? *6?3
1?.
conv2d_20_input?????????
?2?
.__inference_sequential_20_layer_call_fn_757975
.__inference_sequential_20_layer_call_fn_758483
.__inference_sequential_20_layer_call_fn_758508
.__inference_sequential_20_layer_call_fn_758161?
???
FullArgSpec1
args)?&
jself
jinputs

jtraining
jmask
varargs
 
varkw
 
defaults?
p 

 

kwonlyargs? 
kwonlydefaults? 
annotations? *
 
?2?
E__inference_conv2d_20_layer_call_and_return_conditional_losses_758519?
???
FullArgSpec
args?
jself
jinputs
varargs
 
varkw
 
defaults
 

kwonlyargs? 
kwonlydefaults
 
annotations? *
 
?2?
*__inference_conv2d_20_layer_call_fn_758528?
???
FullArgSpec
args?
jself
jinputs
varargs
 
varkw
 
defaults
 

kwonlyargs? 
kwonlydefaults
 
annotations? *
 
?2?
M__inference_module_wrapper_14_layer_call_and_return_conditional_losses_758546
M__inference_module_wrapper_14_layer_call_and_return_conditional_losses_758564?
???
FullArgSpec
args?
jself
varargsjargs
varkwjkwargs
defaults? 

kwonlyargs?

jtraining%
kwonlydefaults?

trainingp 
annotations? *
 
?2?
2__inference_module_wrapper_14_layer_call_fn_758577
2__inference_module_wrapper_14_layer_call_fn_758590?
???
FullArgSpec
args?
jself
varargsjargs
varkwjkwargs
defaults? 

kwonlyargs?

jtraining%
kwonlydefaults?

trainingp 
annotations? *
 
?2?
L__inference_max_pooling2d_20_layer_call_and_return_conditional_losses_757850?
???
FullArgSpec
args?
jself
jinputs
varargs
 
varkw
 
defaults
 

kwonlyargs? 
kwonlydefaults
 
annotations? *@?=
;?84????????????????????????????????????
?2?
1__inference_max_pooling2d_20_layer_call_fn_757856?
???
FullArgSpec
args?
jself
jinputs
varargs
 
varkw
 
defaults
 

kwonlyargs? 
kwonlydefaults
 
annotations? *@?=
;?84????????????????????????????????????
?2?
F__inference_flatten_20_layer_call_and_return_conditional_losses_758596?
???
FullArgSpec
args?
jself
jinputs
varargs
 
varkw
 
defaults
 

kwonlyargs? 
kwonlydefaults
 
annotations? *
 
?2?
+__inference_flatten_20_layer_call_fn_758601?
???
FullArgSpec
args?
jself
jinputs
varargs
 
varkw
 
defaults
 

kwonlyargs? 
kwonlydefaults
 
annotations? *
 
?2?
D__inference_dense_40_layer_call_and_return_conditional_losses_758612?
???
FullArgSpec
args?
jself
jinputs
varargs
 
varkw
 
defaults
 

kwonlyargs? 
kwonlydefaults
 
annotations? *
 
?2?
)__inference_dense_40_layer_call_fn_758621?
???
FullArgSpec
args?
jself
jinputs
varargs
 
varkw
 
defaults
 

kwonlyargs? 
kwonlydefaults
 
annotations? *
 
?2?
D__inference_dense_41_layer_call_and_return_conditional_losses_758632?
???
FullArgSpec
args?
jself
jinputs
varargs
 
varkw
 
defaults
 

kwonlyargs? 
kwonlydefaults
 
annotations? *
 
?2?
)__inference_dense_41_layer_call_fn_758641?
???
FullArgSpec
args?
jself
jinputs
varargs
 
varkw
 
defaults
 

kwonlyargs? 
kwonlydefaults
 
annotations? *
 
?B?
$__inference_signature_wrapper_758248conv2d_20_input"?
???
FullArgSpec
args? 
varargs
 
varkwjkwargs
defaults
 

kwonlyargs? 
kwonlydefaults
 
annotations? *
 
?2?
R__inference_batch_normalization_14_layer_call_and_return_conditional_losses_758659
R__inference_batch_normalization_14_layer_call_and_return_conditional_losses_758677?
???
FullArgSpec)
args!?
jself
jinputs

jtraining
varargs
 
varkw
 
defaults?
p 

kwonlyargs? 
kwonlydefaults? 
annotations? *
 
?2?
7__inference_batch_normalization_14_layer_call_fn_758690
7__inference_batch_normalization_14_layer_call_fn_758703?
???
FullArgSpec)
args!?
jself
jinputs

jtraining
varargs
 
varkw
 
defaults?
p 

kwonlyargs? 
kwonlydefaults? 
annotations? *
 ?
!__inference__wrapped_model_757844?
,-./ !&'@?=
6?3
1?.
conv2d_20_input?????????
? "3?0
.
dense_41"?
dense_41?????????
?
R__inference_batch_normalization_14_layer_call_and_return_conditional_losses_758659?,-./M?J
C?@
:?7
inputs+??????????????????????????? 
p 
? "??<
5?2
0+??????????????????????????? 
? ?
R__inference_batch_normalization_14_layer_call_and_return_conditional_losses_758677?,-./M?J
C?@
:?7
inputs+??????????????????????????? 
p
? "??<
5?2
0+??????????????????????????? 
? ?
7__inference_batch_normalization_14_layer_call_fn_758690?,-./M?J
C?@
:?7
inputs+??????????????????????????? 
p 
? "2?/+??????????????????????????? ?
7__inference_batch_normalization_14_layer_call_fn_758703?,-./M?J
C?@
:?7
inputs+??????????????????????????? 
p
? "2?/+??????????????????????????? ?
E__inference_conv2d_20_layer_call_and_return_conditional_losses_758519l7?4
-?*
(?%
inputs?????????
? "-?*
#? 
0????????? 
? ?
*__inference_conv2d_20_layer_call_fn_758528_7?4
-?*
(?%
inputs?????????
? " ?????????? ?
D__inference_dense_40_layer_call_and_return_conditional_losses_758612] !0?-
&?#
!?
inputs??????????*
? "%?"
?
0?????????d
? }
)__inference_dense_40_layer_call_fn_758621P !0?-
&?#
!?
inputs??????????*
? "??????????d?
D__inference_dense_41_layer_call_and_return_conditional_losses_758632\&'/?,
%?"
 ?
inputs?????????d
? "%?"
?
0?????????

? |
)__inference_dense_41_layer_call_fn_758641O&'/?,
%?"
 ?
inputs?????????d
? "??????????
?
F__inference_flatten_20_layer_call_and_return_conditional_losses_758596a7?4
-?*
(?%
inputs????????? 
? "&?#
?
0??????????*
? ?
+__inference_flatten_20_layer_call_fn_758601T7?4
-?*
(?%
inputs????????? 
? "???????????*?
L__inference_max_pooling2d_20_layer_call_and_return_conditional_losses_757850?R?O
H?E
C?@
inputs4????????????????????????????????????
? "H?E
>?;
04????????????????????????????????????
? ?
1__inference_max_pooling2d_20_layer_call_fn_757856?R?O
H?E
C?@
inputs4????????????????????????????????????
? ";?84?????????????????????????????????????
M__inference_module_wrapper_14_layer_call_and_return_conditional_losses_758546~,-./G?D
-?*
(?%
args_0????????? 
?

trainingp "-?*
#? 
0????????? 
? ?
M__inference_module_wrapper_14_layer_call_and_return_conditional_losses_758564~,-./G?D
-?*
(?%
args_0????????? 
?

trainingp"-?*
#? 
0????????? 
? ?
2__inference_module_wrapper_14_layer_call_fn_758577q,-./G?D
-?*
(?%
args_0????????? 
?

trainingp " ?????????? ?
2__inference_module_wrapper_14_layer_call_fn_758590q,-./G?D
-?*
(?%
args_0????????? 
?

trainingp" ?????????? ?
I__inference_sequential_20_layer_call_and_return_conditional_losses_758191}
,-./ !&'H?E
>?;
1?.
conv2d_20_input?????????
p 

 
? "%?"
?
0?????????

? ?
I__inference_sequential_20_layer_call_and_return_conditional_losses_758221}
,-./ !&'H?E
>?;
1?.
conv2d_20_input?????????
p

 
? "%?"
?
0?????????

? ?
I__inference_sequential_20_layer_call_and_return_conditional_losses_758416t
,-./ !&'??<
5?2
(?%
inputs?????????
p 

 
? "%?"
?
0?????????

? ?
I__inference_sequential_20_layer_call_and_return_conditional_losses_758458t
,-./ !&'??<
5?2
(?%
inputs?????????
p

 
? "%?"
?
0?????????

? ?
.__inference_sequential_20_layer_call_fn_757975p
,-./ !&'H?E
>?;
1?.
conv2d_20_input?????????
p 

 
? "??????????
?
.__inference_sequential_20_layer_call_fn_758161p
,-./ !&'H?E
>?;
1?.
conv2d_20_input?????????
p

 
? "??????????
?
.__inference_sequential_20_layer_call_fn_758483g
,-./ !&'??<
5?2
(?%
inputs?????????
p 

 
? "??????????
?
.__inference_sequential_20_layer_call_fn_758508g
,-./ !&'??<
5?2
(?%
inputs?????????
p

 
? "??????????
?
$__inference_signature_wrapper_758248?
,-./ !&'S?P
? 
I?F
D
conv2d_20_input1?.
conv2d_20_input?????????"3?0
.
dense_41"?
dense_41?????????
