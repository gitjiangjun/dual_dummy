# generated from rosidl_generator_py/resource/_idl.py.em
# with input from arm_control:msg/TrajectoryPoint.idl
# generated code does not contain a copyright notice


# Import statements for member types

# Member 'positions'
import array  # noqa: E402, I100

import builtins  # noqa: E402, I100

import math  # noqa: E402, I100

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_TrajectoryPoint(type):
    """Metaclass of message 'TrajectoryPoint'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('arm_control')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'arm_control.msg.TrajectoryPoint')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__trajectory_point
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__trajectory_point
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__trajectory_point
            cls._TYPE_SUPPORT = module.type_support_msg__msg__trajectory_point
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__trajectory_point

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class TrajectoryPoint(metaclass=Metaclass_TrajectoryPoint):
    """Message class 'TrajectoryPoint'."""

    __slots__ = [
        '_arm_name',
        '_positions',
        '_time_from_start',
    ]

    _fields_and_field_types = {
        'arm_name': 'string',
        'positions': 'sequence<double>',
        'time_from_start': 'double',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.UnboundedString(),  # noqa: E501
        rosidl_parser.definition.UnboundedSequence(rosidl_parser.definition.BasicType('double')),  # noqa: E501
        rosidl_parser.definition.BasicType('double'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.arm_name = kwargs.get('arm_name', str())
        self.positions = array.array('d', kwargs.get('positions', []))
        self.time_from_start = kwargs.get('time_from_start', float())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.arm_name != other.arm_name:
            return False
        if self.positions != other.positions:
            return False
        if self.time_from_start != other.time_from_start:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @builtins.property
    def arm_name(self):
        """Message field 'arm_name'."""
        return self._arm_name

    @arm_name.setter
    def arm_name(self, value):
        if __debug__:
            assert \
                isinstance(value, str), \
                "The 'arm_name' field must be of type 'str'"
        self._arm_name = value

    @builtins.property
    def positions(self):
        """Message field 'positions'."""
        return self._positions

    @positions.setter
    def positions(self, value):
        if isinstance(value, array.array):
            assert value.typecode == 'd', \
                "The 'positions' array.array() must have the type code of 'd'"
            self._positions = value
            return
        if __debug__:
            from collections.abc import Sequence
            from collections.abc import Set
            from collections import UserList
            from collections import UserString
            assert \
                ((isinstance(value, Sequence) or
                  isinstance(value, Set) or
                  isinstance(value, UserList)) and
                 not isinstance(value, str) and
                 not isinstance(value, UserString) and
                 all(isinstance(v, float) for v in value) and
                 all(not (val < -1.7976931348623157e+308 or val > 1.7976931348623157e+308) or math.isinf(val) for val in value)), \
                "The 'positions' field must be a set or sequence and each value of type 'float' and each double in [-179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000, 179769313486231570814527423731704356798070567525844996598917476803157260780028538760589558632766878171540458953514382464234321326889464182768467546703537516986049910576551282076245490090389328944075868508455133942304583236903222948165808559332123348274797826204144723168738177180919299881250404026184124858368.000000]"
        self._positions = array.array('d', value)

    @builtins.property
    def time_from_start(self):
        """Message field 'time_from_start'."""
        return self._time_from_start

    @time_from_start.setter
    def time_from_start(self, value):
        if __debug__:
            assert \
                isinstance(value, float), \
                "The 'time_from_start' field must be of type 'float'"
            assert not (value < -1.7976931348623157e+308 or value > 1.7976931348623157e+308) or math.isinf(value), \
                "The 'time_from_start' field must be a double in [-1.7976931348623157e+308, 1.7976931348623157e+308]"
        self._time_from_start = value
